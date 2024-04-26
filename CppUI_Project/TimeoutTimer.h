#pragma once

using namespace System;
using namespace System::Timers;

ref class TimeoutTimer
{
private:
	Timer^ _timeout;

	Void SendCancelEvent(Object^ sender, ElapsedEventArgs^ e);

public:
	TimeoutTimer(Int32 timeoutMs);
};

