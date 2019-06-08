#include <stdio.h>
#include <memory>
#include <stdlib.h>


typedef unsigned int uint32_t;
typedef unsigned char uint8;




static inline char isPowerOf2(uint32_t n) {
	return n != 0 && (n&(n-1)==0);
}




struct kfifo {
	uint8 *buffer;
	unsigned int in; // ����ָ��
	uint32_t out; // ���ָ��
	uint32_t size; // ��������С������Ϊ2�Ĵ���

	kfifo(uint32_t _size)
	{
		if (!isPowerOf2(_size))
			_size = roundup_power_of_2(_size);

		buffer = new uint8_t[_size];
		in = 0;
		out = 0;
		size = _size;
	}


	// ����ʵ��д�뻺�����е�����
	uint32_t put(const uint8_t *data, uint32_t len)
	{
		// ��ǰ���������пռ�
		len = min(len, size - in + out);

		// ��ǰinλ�õ�bufferĩβ�ĳ���
		auto l = min(len, size - (in  & (size - 1)));

		// ���ȸ������ݵ�[in��buffer��ĩβ]
		memcpy(buffer + (in & (size - 1)), data, l);

		// ����ʣ������ݣ�����У���[buffer����ʼλ��,...]
		memcpy(buffer, data + l, len - l);

		in += len; // ֱ�Ӽӣ�����ģ���㡣�����ʱ����buffer�Ŀ�ʼλ�����¿�ʼ

		return len;
	}

	// ����ʵ�ʶ�ȡ�����ݳ���
	uint32_t get(uint8_t *data, uint32_t len)
	{
		// �������е����ݳ���
		len = min(len, in - out);

		// ���ȴ�[out,buffer end]��ȡ����
		auto l = min(len, size - (out & (size - 1)));
		memcpy(data, buffer + (out & (size - 1)), l);

		// ��[buffer start,...]��ȡ����
		memcpy(data + l, buffer, len - l);

		out += len; // ֱ�Ӽӣ�����ģ���㡣����󣬴�buffer����ʼλ�����¿�ʼ

		return len;
	}






	int main(int argc, const char *argvs[], const char * envs[]) {
	
	
		return 0;
	}