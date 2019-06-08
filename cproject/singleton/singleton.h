#ifndef  __SINGLETON_H__
#define  __SINGLETON_H__

template <typename T>
class Singleton{
	typedef T TypeValue;
	typedef Singleton SelfValue;
	Singleton();
	Singleton(SelfValue&);

	friend T;//friend+����˽��struct �� ���� �ͱ��� ��һ��ģʽ


public:
	static TypeValue& getInstance() {
		static TypeValue ins;
		//2 �ص� ������
		trigger.nullAction();
		return ins;
	}

private:

	struct InternalCreatorTrigger {
		//1 ��������������
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
//Singleton+T������ û������ InternalCreatorTrigger ���ͣ���Ϊ
//T������û���������ڲ�Singleton��Ҳ��˵����������Singleton<T> �޷��������� ˽��InternalCreatorTrigger

//typename �ǵü��ϣ���Ϊ����T ��������� ������·�������µ������� ������ͨ��typename ע����������벻��ʶ
typename Singleton<T>::InternalCreatorTrigger Singleton<T>::trigger;

#endif // ! __SINGLETON_H__



