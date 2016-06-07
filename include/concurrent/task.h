// task.h
#pragma once
#include <fn.h>
#include "concurrent/future.h"

#include <memory>
#include <thread>

using std::shared_ptr;

namespace brando {
	namespace concurrent {
		// *** Forward Declaration
		template<typename T> class Task;
		struct Executor;

		/*
			 Task<T> - a computation that can be executed to produce a value of type T
			 */
		template<typename T> 
			class Task {
				public:
					auto run() -> T { return f(); };
					auto runAsync(Executor& ex) -> Future<T>;

					Task(function<T()> f_) : f(f_) {}

					static auto delay(function<T()> f) { return Task(f); }

					/*
						 Task probably needs to be a free Monad that is interpreted as Id or Future when run
						 */
					template<typename U>
						auto map(function<U(T)> ff) -> Task<U> { return Task<U>([=] { return ff(f()); }); };

					//auto bind(Fn<T,Task<U>>) -> Task<U>
				private:
					function<T()> f;
			};
	};
}

#include "concurrent/executor.h"
template<typename T>
	auto brando::concurrent::Task<T>::runAsync(brando::concurrent::Executor& ex) -> Future<T> { (void)ex; return future(f()); };
//	auto brando::concurrent::Task<T>::runAsync(brando::concurrent::Executor& ex) -> Future<T> { return ex.execute(*this); };

