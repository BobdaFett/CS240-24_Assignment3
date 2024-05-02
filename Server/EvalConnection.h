#pragma once

#include "Calc.h"

using namespace System;
using namespace System::IO;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Threading;

ref class EvalConnection
{
private:
	Socket^ _socket;
	NetworkStream^ _socketStream;
	BinaryReader^ _reader;
	BinaryWriter^ _writer;

	Boolean _connected;
	
public:
	/// <summary>
	/// Creates an instance of the EvalConnection class.
	/// This is a thread handler which allows the server to handle multiple
	/// connections at once.
	/// </summary>
	/// <param name="connection -">The Socket that contains the connection information.</param>
	EvalConnection(Socket^ connection);

	/// <summary>
	/// Handles the TCP connection handshake to establish a protocol.
	/// Throws an error if something goes wrong.
	/// </summary>
	/// <returns></returns>
	Void ConnectionHandshake();

	/// <summary>
	/// Handles getting and constructing the string from the client.
	/// </summary>
	Void ProcessExpression();
};
