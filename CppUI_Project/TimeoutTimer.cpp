#include "TimeoutTimer.h"

TimeoutTimer::TimeoutTimer(Int32 timeoutMs) {
	_timeout = gcnew System::Timers::Timer(timeoutMs);
	_timeout->Elapsed += gcnew ElapsedEventHandler(this, &TimeoutTimer::SendCancelEvent);
	_timeout->Start();
}

Void TimeoutTimer::SendCancelEvent(Object^ sender, ElapsedEventArgs^ e) {
	_timeout->Stop();
	throw gcnew TimeoutException();
}