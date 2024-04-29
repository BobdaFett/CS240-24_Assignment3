#include "EvalConnection.h"

EvalConnection::EvalConnection(Socket^ connection) {
	_socket = connection;
	_socketStream = gcnew NetworkStream(_socket);
	_reader = gcnew BinaryReader(_socketStream);
	_writer = gcnew BinaryWriter(_socketStream);
	_connected = false;
}

Void EvalConnection::ConnectionHandshake() {
	// Attempt to handshake with the client.
	// This method should NOT change anything about the connection on its own.
	String^ threadName = Thread::CurrentThread->Name;
	Console::WriteLine("{0}: Attempting handshake.", threadName);
	
	// Wait for SYN
	Console::WriteLine("{0}: Attempting to read SYN", threadName);
	String^ response = _reader->ReadString();
	if (response != "SYN") throw gcnew Exception("Client did not attempt to sync with server.");
	
	// Send SYN-ACK
	Console::WriteLine("{0}: Attempting to send SYN-ACK", threadName);
	_writer->Write("SYN-ACK");

	// Wait for ACK
	Console::WriteLine("{0}: Attempting to read ACK", threadName);
	response = _reader->ReadString();
	if (response != "ACK") throw gcnew Exception("Client responded with unknown code.");

	_connected = true;
}

Void EvalConnection::ProcessExpression() {
	// Check if the socket is connected.
	if (!_connected) {
		Console::WriteLine("Server is not properly connected. Ensure that ConnectionHandshake completes.");
		return;
	}

	String^ threadName = Thread::CurrentThread->Name;

	// Get the information from the network stream and work with it.
	String^ evalString = "";

	Console::WriteLine("{0}: Getting information from client...", threadName);

	while (true) {
		// We must check for new packets constantly, until we've found an EOS token.
		Char temp = _reader->ReadChar();
		Console::WriteLine("{0}: Read {1}", threadName, temp);
		if (temp == 'E')
			break;

		// Add this string to the end of the current evalString.
		// This is a bad security practice, but we will assume  that verification
		// of the tokens has been done by the client for now.
		Int32 parsedTemp = 0;
		Boolean canParse = Int32::TryParse(temp.ToString(), parsedTemp);

		if (canParse || temp == '+' || temp == '-' || temp == '(' || temp == ')' || temp == '/' || temp == '*') {
			// This is a valid token, accept and add to evalString.
			evalString += temp;
			_writer->Write("ACK");
		}
		else {
			// Tell the client that it sent an invalid token.
			// At this point, it will try to send the token again, but the server will simply loop.
			_writer->Write("NAK");
		}
	}
	
	Console::WriteLine("{0}: Evaluating expression {1}", threadName, evalString);

	// Once we are done getting the string, we need to evaluate the string.
	Double value = Calc::EvaluateExpression(evalString);

	Console::WriteLine("{0}: Sending {1} to client.", threadName, value);

	// Send the computed value back to the client, then wait for a verification.
	while (true) {
		_writer->Write(value.ToString());
		String^ response = _reader->ReadString();

		if (response == "ACK")
			break;
	}

	// We are done - close the connection.
	_socketStream->Close();
	_socket->Close();

	Console::WriteLine("{0}: Closed connection.", threadName);
}