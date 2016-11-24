// brando.h
//
// include this file in your project and #define BRANDO_MAIN to pull in required single-compilation code

#ifdef BRANDO_MAIN
#include "range.h"
#include "unit.h"
#include "concurrent/executor.h"
#include "concurrent/time.h"

namespace brando {
	Unit unit() { return Unit(); }

  namespace concurrent {
		Milliseconds milliseconds;
		Seconds seconds;
		Minutes minutes;
		Hours hours;

    void executeFn( Executor& ex, function<void()> f ) {
      //auto t = defer( f(); return unit(); );
      auto t = task([=]{ f(); return unit(); });
      ex.executeImpl( t );
    };
  }

	auto foreach(int n) -> ForeachBuilder { return ForeachBuilder(n); }
}

#endif