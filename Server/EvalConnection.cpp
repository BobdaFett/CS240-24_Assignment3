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
	//Console::WriteLine("{0}: Attempting handshake.", threadName);
	
	// Wait for SYN
	//Console::WriteLine("{0}: Attempting to read SYN", threadName);
	String^ response = _reader->ReadString();
	if (response != "SYN") throw gcnew Exception("Client did not attempt to sync with server.");
	
	// Send SYN-ACK
	//Console::WriteLine("{0}: Attempting to send SYN-ACK", threadName);
	_writer->Write("SYN-ACK");

	// Wait for ACK
	//Console::WriteLine("{0}: Attempting to read ACK", threadName);
	response = _reader->ReadString();
	if (response != "ACK") throw gcnew Exception("Client responded with unknown code.");

	_connected = true;
}

Void EvalConnection::ProcessExpression() {
	String^ threadName = Thread::CurrentThread->Name;

	Console::Write("{0}: Attempting to connect to client... ", threadName);
	Int32 connectionAttempts = 0;
	while (!_connected && connectionAttempts <= 3) {
		try {
			connectionAttempts++;
			this->ConnectionHandshake();
		}
		catch (Exception^ e) {
			// Display some sort of error message.
			Console::Write("Failed.\nError: {0}\n{1}: Retrying connection... ", e->Message, threadName);
		}
	}
	if (connectionAttempts == 3) {
		// Abort process
		Console::WriteLine("Aborting.");
		return;
	}

	Console::WriteLine("Done.");

	// Get the information from the network stream and work with it.
	String^ evalString = "";

	Console::WriteLine("{0}: Getting information from client...", threadName);

	try {
		while (true) {
			// We must check for new packets constantly, until we've found an EOS token.
			String^ temp = _reader->ReadString();
			Console::WriteLine("{0}: Read {1}", threadName, temp);
			if (temp == "EOS")
				break;

			// Add this string to the end of the current evalString.
			// This is a bad security practice, but we will assume  that verification
			// of the tokens has been done by the client for now.
			Int32 parsedTemp = 0;
			Boolean canParse = Int32::TryParse(temp, parsedTemp);

			if (canParse || temp == "+" || temp ==  "-" || temp == "(" || temp == ")" || temp == "/" || temp == "*") {
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
	}
	catch (SocketException^ e) {
		Console::WriteLine("{0}: SocketException: {1}", threadName, e->Message);
		return;
	}
	catch (Exception^ e) {
		// Unpredictable - show message and abort process.
		Console::WriteLine("{0}: Exception: {1}", threadName, e->Message);
		return;
	}
	
	Console::WriteLine("{0}: Evaluating expression {1}", threadName, evalString);

	// Once we are done getting the string, we need to evaluate the string.
	Double value;
	try {
		value = Calc::EvaluateExpression(evalString);
	}
	catch (Exception^) {
		// The only reason this will fail is due to incorrect characters.
		// Send this information to the client.
		_writer->Write("SYNTAX");
	}

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