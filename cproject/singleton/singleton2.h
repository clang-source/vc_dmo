#ifndef __SINGLETON2_H__
#define __SINGLETON2_H__

//���븴��
//�߼�����
//ģ�岻�ÿ��Ƕദ�ظ��������⣬��Ϊģ���ǳ���Ĳ�û��ʵ��

template <class T>

class Singleton2 {
	typedef Singleton2 ProxyType;
	typedef T TargetType;

	friend T;
private:
	Singleton2(ProxyType&);
	Singleton2();
	ProxyType& operator= (const ProxyType&);
	
public:
	static TargetType& getInstance()
	{
		static TargetType instance;
		//2 �ص�
		creator.nullCallback();
		return  instance;
	}
private:
	class CreatorTriiger {
	public:
		CreatorTriiger() {
			//1 ����ʵ���� ��������
			//initailize target instance
			ProxyType::getInstance();
		}
		//ensure trigger  CreatorTriiger instance intialize
		void nullCallback() {
		}

	};

	static CreatorTriiger creator;

};
 
template<class T>
typename Singleton2<T>::CreatorTriiger Singleton2<T>::creator;


#endif