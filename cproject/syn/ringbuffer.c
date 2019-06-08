


#define LEN 100


char queueBuf[LEN];

int head = 0, tail = 0;


struct RingBuffer_;

typedef struct RingBuffer_ RingBuffer;
//write tail
//read head
#define RINGSIZE 512
struct RingBuffer_ {
	char data[RINGSIZE];

	int head_r;
	int tail_w;

};

RingBuffer *RingBufferNew() {
	RingBuffer *rf = (RingBuffer*)malloc(sizeof(RingBuffer));
	memset(rf,0,sizeof(RingBuffer));
	return RingBufferConstruct(rf);

}

RingBuffer *RingBufferConstruct(RingBuffer* this) {

	return this;
}

int RingBufferIsEmpty(RingBuffer*this) {
	return this->tail_w == this->head_r;
}

//a % b == a & (b - 1)
int RingBufferIsFull(RingBuffer*this) {
	//return (this->tail_w + 1)&(RINGSIZE - 1)==this->head_r;
	return (this->tail_w + 1) % RINGSIZE == this->head_r;
}

int RingBufferPush(RingBuffer*this,char value) {
	if (!RingBufferIsFull(this)) {
		this->data[this->tail_w + 1] = value;
		this->tail_w = (this->tail_w + 1) % RINGSIZE;
	}
}

char RingBufferPop(RingBuffer*this) {
	char ret = 0;
	if (!RingBufferIsEmpty(this)) {
		ret = this->data[this->head_r];
		this->head_r = (this->head_r + 1) % RINGSIZE;
	}

	return ret;
}





int main(int argc, const char *argvs[]) {



	return 0;
}