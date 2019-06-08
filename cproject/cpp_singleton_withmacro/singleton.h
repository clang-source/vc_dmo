#ifndef __SINGLETON_H__
#define __SINGLETON_H__


#define SINGLETON_TEMPL(T)\
	private:\
		T();\
		T(const T&);\
		T& operator=(const T&);\
		~T();\
	public:\
		static T& getInstance() {\
			static T ins;\
			return ins;\
		}



#if _WIN32
 void * atoimic_ulong_cas(void** addr, void* old, void* newValue) {
	 void * ret = 0;


	return  ret;
}
#elif _WIN64
 void * atoimic_ulong_cas(void** addr, void* old, void* newValue) {
	 void * ret = 0;


	return  ret;
}

#elif __linux__ || __unix__

 void * atoimic_ulong_cas(void** addr, void* old, void* newValue) {
	 void * ret = 0;
	//cmpxchg new ,[ptr]  compare with eax value(oldvalue)
	__asm volatile(
	"lock;cmpxchg %n,%n;"
		:"=a"(ret)
		: "m"(*addr), "0"(old), "r"(newValue)
		: "cc", "memory"
		);
	return  ret;
}

#endif

#define SINGLETON_LAZY_TEMPL(T)\
	private:\
		 static T* ins;\
	private:\
		T(); \
		T(const T&); \
		T& operator=(const T&); \
		~T(); \
	public:\
		static T& getInstance() {\
		if (ins == 0) {\
			void *mem = malloc(sizeof(T));\
			if (0 != atoimic_ulong_cas(&ins, 0, mem)) {\
				if (mem != 0) {\
					free(mem);\
					mem = 0;\
				}\
			}\
		} \
			return ins; \
	}





		
#endif

 