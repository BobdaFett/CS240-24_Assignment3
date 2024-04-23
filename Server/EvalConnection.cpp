#include "EvalConnection.h"

EvalConnection::EvalConnection(Socket^ connection) {
	_socket = connection;
	_socketStream = gcnew NetworkStream(_socket);
	_reader = gcnew StreamReader(_socketStream);
	_writer = gcnew StreamWriter(_socketStream);
}

Void EvalConnection::ConnectionHandshake() {
	// Attempt to handshake with the socket.
	// This method should NOT change anything about the connection on its own.
	
	// Wait for SYN
	String^ response = _reader->ReadLine();
	if (response != "SYN") throw gcnew Exception("Client did not attempt to sync with server.");
	
	// Send SYN-ACK
	_writer->WriteLine("SYN-ACK");

	// Wait for ACK
	response = _reader->ReadLine();
	if (response != "ACK") throw gcnew Exception("Client responded with unknown code.");
}

Void EvalConnection::ProcessExpression() {
	// Get the information from the network stream and work with it.
	String^ evalString = "";

	while (true) {
		// We must check for new packets constantly, until we've found an EOS token.
		String^ temp = _reader->ReadLine();
		if (temp == "EOS")
			break;

		// Add this string to the end of the current evalString.
		// This is a bad security practice, but we will assume  that verification
		// of the tokens has been done by the client for now.
		// TODO Create restriction for accepted tokens.
		evalString += temp;

		// Send a verification token to the client.
		_writer->Write("ACK");
	}
	
	// Once we are done getting the string, we need to evaluate the string.
	Double value = Calc::EvaluateExpression(evalString);

	// Send the computed value back to the client, then wait for a verification.
	while (true) {
		_writer->WriteLine(value.ToString());
		String^ response = _reader->ReadLine();

		if (response == "ACK")
			break;
	}

	// We are done - close the connection.
	_socketStream->Close();
	_socket->Close();
}