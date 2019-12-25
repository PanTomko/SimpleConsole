#pragma once
#include <vector>

#include <algorithm>
#include <memory>

#define DllExport __declspec( dllexport )

namespace sc
{
	template<class ... Args>
	class DllExport SubscriberBase {
	public:
		virtual void call(Args... parms) = 0;
		virtual bool is(void*_t) = 0;

		SubscriberBase() {};
		~SubscriberBase() {};
	};

	template<class T, class ... Args>
	class Subscriber : public SubscriberBase<Args...> {
	public:
		typedef void(T::*obj_func_wsk)(Args...);
		Subscriber(T * _o_wsk, obj_func_wsk _f_wsk) : o_wsk{ _o_wsk }, f_wsk{ _f_wsk } {};

		virtual void call(Args ...parms) final {
			(o_wsk->*f_wsk)(parms...);
		}

		bool is(void* _t) final { return _t == (void*)o_wsk; }

		obj_func_wsk f_wsk;
		T * o_wsk;
	};

	template <class ... Args>
	class EventObserver {
	public:
		typedef void(*func_wsk)(Args...);

		void notify(Args ... parms) {
			for (auto & sub : subscribers) sub->call(parms...);
			for (auto & sub : global_subscribers) sub(parms...);
		}

		void addSubscriber(func_wsk f_wsk) {
			global_subscribers.push_back(f_wsk);
		}

		template<class T>
		void addSubscriber(T * o_wsk, void (T::*f_wsk)(Args...)) {
			subscribers.push_back(new Subscriber<T, Args...>{ o_wsk, f_wsk });
		}

		template<class T>
		void removeSubscriber(T * o_wsk) {
			auto x = std::remove_if(subscribers.begin(), subscribers.end(), [&](SubscriberBase<Args...>*sub) {
				if (sub->is((void*)o_wsk)) return true;
				else return false;
				});

			if (x != subscribers.end()) subscribers.erase(x);
		}

		void removeSubscriber(func_wsk f_wsk) {
			global_subscribers.erase(
				std::remove_if(
					global_subscribers.begin(),
					global_subscribers.end(), [&](func_wsk sub) {
						if (sub == f_wsk) return true;
						else return false;
					}));
		}

		EventObserver() {};
		~EventObserver() {};

	private:
		std::vector<SubscriberBase<Args...>*>subscribers;
		std::vector<func_wsk>global_subscribers;
	};
}