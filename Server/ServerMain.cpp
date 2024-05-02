using namespace System;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Threading;

#include "EvalConnection.h"

int main() {
	Console::WriteLine("Starting server...");
	Console::Write("Setting up listener.... ");

	IPAddress^ ip = (IPAddress^)Dns::GetHostEntry(Dns::GetHostName())->AddressList[0];
	IPEndPoint^ endpoint = gcnew IPEndPoint(ip, 1234);

	Socket^ listener = gcnew Socket(ip->AddressFamily, SocketType::Stream, ProtocolType::Tcp);
	listener->Bind(endpoint);
	listener->Listen(3);  // Allow 3 connections to be held in queue.

	Console::WriteLine("Done - socket bound to address {0}", ip);

	// Start checking for connections.
	// The server will run until told to stop, by C-c or otherwise.
	// Later, this may be changed into a GUI.
	int numConnections = 0;  // This is not related to the number of active connections.
	while (true) {
		// Grab the connection.
		Socket^ connection = listener->Accept();
		numConnections++;

		// Use the connection to create a new EvalConnection object.
		EvalConnection^ handler = gcnew EvalConnection(connection);

		// Use the handler to create a new thread which will process the message.
		Thread^ process = gcnew Thread(gcnew ThreadStart(handler, &EvalConnection::ProcessExpression));
		process->Name = "Connection" + numConnections;
		process->Start();
	}

	return 0;
}