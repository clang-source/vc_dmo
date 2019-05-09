#include "constructs.h"
#include <stdio.h>
struct _Animial;
typedef struct _Animial Animial;

struct _Animial {
	int age;
	int weight;
	void(*eat)(Animial* this, const char * food);//�����麯������Ϊ�������ʵ���麯����ֱ��type_method(this)�Ϳ���ʵ����
	void(*destruct)(Animial* this);//�麯��
};

//������һ��û��ʵ�־��ǳ����࣬���ж�û��ʵ�� ���ǽӿ�

void Animal_Eat(Animial* this, const char * food);
void AnimalDestruct(Animial* this);

Animial* AnimialConstruct(Animial* this, int age, int weight) {
	this->age = age;
	this->weight = weight;
	this->eat = Animal_Eat;
	this->destruct = AnimalDestruct;
	return this;
}


void Animal_Eat(Animial* this, const char * food) {

	printf("animal eat %s \n", food);
}

void AnimalDestruct(Animial* this) {
	printf("animal destory...  \n");
}


struct _Dog;
typedef struct _Dog Dog;

#define NAME_SIZE_LIMIT 30

//�����������ڴ��ǣ���һ��ģ��ͷ����棬ɾ������ ��Ϊ��һ���Եģ�ֻ��Ҫɾ��һ��
struct _Dog {
	Animial base;
    char name[NAME_SIZE_LIMIT];
	void(*eat)(Dog* this, const char *food);
	void(*destruct)(Dog* this);
};

// ���캯�� Ҳ��һ�����������������Կ��ƹ��������ڵ���Դ�������ڣ��������������Ŀ��ƣ���ϵͳ����
void DogEat(Dog* this, const char *food);
void DogDestruct(Dog* this);

Dog * DogConstruct(Dog *this,int age,int weight,const char *name) {
	AnimialConstruct((Animial*)this,age,weight);
	this->base.age = age;
	this->base.weight = weight;
	this->eat = DogEat;
	this->base.eat = DogEat;
	this->destruct = DogDestruct;
	return  this;

}


void DogEat(Dog* this, const char *food) {
	printf("dog is eating %s \n",food);
}

//��Ҫ�� �����������棬�ͷ��Լ��ڴ棬��Ϊ ������ �����е�һ����������
void DogDestruct(Dog* this) {
	printf("dog this->name:%s  destroy \n",this->name);
}



//������������ϵ����ã�����о���������

int main(int argc, const char *argvs[]) {
	Animial * a = NEW(Animial, 18, 65);
	a->eat(a, " milk");
	VIRTUAL_DELETE(a);
	a =(Animial *) NEW(Dog, 10, 20, "wenweiping");

	a->eat(a,"dog bone");

	VIRTUAL_DELETE(a);


	getchar();
	return 0;
}













