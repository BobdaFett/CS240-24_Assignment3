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

	// Send SYN
	//Console::WriteLine("Sending SYN");
	_writer->Write("SYN");

	// Wait for response.
	//Console::WriteLine("Reading...");
	String^ response = _reader->ReadString();
	if (response != "SYN-ACK") throw gcnew IOException("Server failed to respond properly.");

	// Send ACK
	//Console::WriteLine("Sending ACK");
	_writer->Write("ACK");

	_connected = true;
}

Void Form1::ServerConnection::EvaluateExpression() {
	// Attempt the connection handshake.
	Console::Write("Attempting to connect to server.... ");
	Int32 connectionAttempts = 0;
	while (!_connected && connectionAttempts <= 3) {
		try {
			connectionAttempts++;
			this->ConnectionHandshake();
		}
		catch (Exception^) {
			// we would like to try this again a couple more times.
			// Display an error message.
			Console::Write("Failed.\nRetrying connection... ");
		}
	}
	if (connectionAttempts == 3) {
		// The connection has failed. Stop retrying and throw error.
		Console::WriteLine("Aborting.");
		throw gcnew IOException("Connection failed - could not complete connection handshake.");
	}
	Console::WriteLine("Done.");

	Console::WriteLine("Sending string to server...");

	// Initialize random number generator.
	Random^ rand = gcnew Random();

	// Build and send the packets to the server.
	for (int i = 0; i < _evalString->Length; i++) {
		String^ toSend = _evalString[i].ToString();

		// On first send, check if the value should be incorrect.
		// If so, send an "I" instead of the actual string.
		Console::WriteLine("Current chance of incorrect packets: {0}%", _currentForm->_percentInvalid);
		Int32 chance = rand->Next(100);
		Console::WriteLine("Random number: {0}", chance);

		if (chance <= _currentForm->_percentInvalid) {
			// Send an incorrect string.
			_writer->Write("I");
			Console::WriteLine("Sent I");
		}
		else {
			_writer->Write(toSend);
			Console::WriteLine("Sent {0}", toSend);
		}

		// Read for ACK from server.
		String^ response = _reader->ReadString();
		Int32 numRetries = 0;
		
		// Assuming that the client gets a NAK, it has 5 attempts to send something the right way back.
		// Otherwise, this will terminate the connection as the equation will not send properly at all.
		while (response == "NAK" && numRetries < 5) {
			// Send the token again
			_writer->Write(toSend);
			numRetries++;
			Console::WriteLine("Attempting to resend token... attempt {0}", numRetries);

			// Try to get the ACK again.
			response = _reader->ReadString();
		}

		if (numRetries >= 5) {
			// disconnect from the server and throw an error.
			_socket->Close();
			throw gcnew IOException("Network error during evaluation - Retries exceeded.");
		}
	}

	// Send the EOS token to signal the end of the string.
	_writer->Write("EOS");

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
