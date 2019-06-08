#ifndef  __SINGLETON_H__
#define  __SINGLETON_H__

template <typename T>
class Singleton{
	typedef T TypeValue;
	typedef Singleton SelfValue;
	Singleton();
	Singleton(SelfValue&);

	friend T;//friend+定义私有struct 和 方法 和变量 是一种模式


public:
	static TypeValue& getInstance() {
		static TypeValue ins;
		//2 回调 触发者
		trigger.nullAction();
		return ins;
	}

private:

	struct InternalCreatorTrigger {
		//1 主调，单例方法
		InternalCreatorTrigger()
		{
			//start trigger //init
			SelfValue::getInstance();
		}

	public:
		void nullAction() {
		   //null ensurce to trigge initialize  trigger;
		}

	};
	static InternalCreatorTrigger trigger;
};

template <typename T>
//Singleton+T的类型 没法看到 InternalCreatorTrigger 类型，因为
//T的类型没法看到的内部Singleton，也就说明，新类型Singleton<T> 无法看到变量 私有InternalCreatorTrigger

//typename 记得加上，因为基于T 计算出来的 或者链路出来的新导航类型 ，必须通过typename 注名，否则编译不认识
typename Singleton<T>::InternalCreatorTrigger Singleton<T>::trigger;

#endif // ! __SINGLETON_H__



