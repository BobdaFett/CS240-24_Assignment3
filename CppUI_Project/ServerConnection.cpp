#include "Form1.h"

using namespace CppUIProject;

Form1::ServerConnection::ServerConnection(Socket^ socket, String^ evalString, Form1^ currentForm) {
	_socket = socket;
	_stream = gcnew NetworkStream(_socket);
	_reader = gcnew BinaryReader(_stream);
	_writer = gcnew BinaryWriter(_stream);
	_evalString = evalString;
	_connected = false;
	_currentForm = currentForm;
}

Void Form1::ServerConnection::ConnectionHandshake() {
	// Attempt to handshake with the server.
	Console::WriteLine("Attempting handshake with server.");

	// Send SYN
	Console::WriteLine("Sending SYN");
	_writer->Write("SYN");

	// Wait for response.
	Console::WriteLine("Reading...");
	String^ response = _reader->ReadString();
	if (response != "SYN-ACK") throw gcnew Exception("Server failed to respond properly.");

	// Send ACK
	Console::WriteLine("Sending ACK");
	_writer->Write("ACK");

	Console::WriteLine("Connection completed.");

	_connected = true;
}

Void Form1::ServerConnection::EvaluateExpression() {
	// Check if the connection is complete.
	if (!_connected) {
		Console::WriteLine("Client is not properly connected. Ensure that ConnectionHandshake completes.");
		return;
	}

	Console::WriteLine("Sending string to server...");

	// Build and send the packets to the server.
	for (int i = 0; i < _evalString->Length; i++) {
		// Send the char to the server.
		_writer->Write(_evalString[i]);

		Console::WriteLine("Sent {0}", _evalString[i]);

		// Read for ACK from server.
		String^ response = _reader->ReadString();
	}

	// Send the EOS token to signal the end of the string.
	_writer->Write('E');

	Console::WriteLine("Waiting for response from server...");

	// Wait for the server to send a response.
	String^ responseString = _reader->ReadString();
	Int32 response = Int32::Parse(responseString);

	// Send response back to server.
	_writer->Write("ACK");

	Console::WriteLine("Showing computed value: {0}", response);

	// Write this info to the screen.
	_currentForm->Invoke(_currentForm->delegateTotal, response);
}
