#ifndef BUFFER_H
#define BUFFER_H

#include <vector>
using namespace std;

class BufferChunk;

class Buffer
{
public:
	Buffer():used(0){
		buf = new char[SIZE];
	}

	~Buffer(){
		delete [] buf;
	}

	void Free(){
		used = 0;
//		chunk_belong->used --;
	}

	char *buf;
	int used;
	BufferChunk* chunk_belong;
	static const int SIZE = 1024;
};

class BufferChunk
{
public:
	BufferChunk():used(0){
		buf_list = new Buffer[BUF_COUNT];
		for(int i = 0; i < BUF_COUNT; ++i)
			buf_list[i].chunk_belong = this;
	}

	~BufferChunk(){
		delete [] buf_list;
	}

	int NewBuf(vector<Buffer*> &res, int get_size){
		int res_size = 0;
		int i = 0; 
		while(res_size < get_size && i < BUF_COUNT){
			if((buf_list+i)->used == 0){
				res.push_back(buf_list+i);
				res_size += Buffer::SIZE; 
			}
			++i;
		}
		return res_size;
	}

	int FreeSize() const {return BUF_COUNT - used;}
	Buffer *buf_list;	
	int used;
	static const int BUF_COUNT = 1024;
};

class BufferPool
{
public:
	BufferPool(){}

	~BufferPool(){
		for(int i = 0; i < v_buf_chunk.size(); ++i){
			delete v_buf_chunk[i];
		}
	}

	static const int MAX_BUF_SIZE = 1048576; //1024*1024 1M
	int buf_used;
	int buf_count;
	int clear_factor;
	vector<BufferChunk*> v_buf_chunk;

	vector<Buffer*> NewBuf(int size){
		vector<Buffer*> res;
		if(size > MAX_BUF_SIZE) return res;
		int i = 0; 
		while(size > 0 && i < v_buf_chunk.size()){
			size -= v_buf_chunk[i]->NewBuf(res, size);
			++i;
		}
		while(size > 0){
			BufferChunk *tmp = new BufferChunk;
			v_buf_chunk.push_back(tmp);
			size -= tmp->NewBuf(res, size);	
		}
		return res;
	}

	bool FreeBuf(vector<Buffer*> &v_buf){
		for(int i = 0; i < v_buf.size(); ++i){
			v_buf[i] -> Free();
			v_buf[i]->chunk_belong->used --;
		}
	}

	void clear(){
	}
};

#endif
