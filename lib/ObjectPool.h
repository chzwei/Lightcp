#ifndef OBJECT_POOL_H
#define OBJECT_POOL_H

template<typename T>
class ObjectChunk
{
public:
	ObjectChunk();
	ObjectChunk(int size);
	~ObjectChunk();
	T* NewObject();
	bool DeleteObject(T *obj);
	bool IsInchunk(T *obj);
	bool IsFull();
	bool IsEmpty();

	ObjectChunk<T> *previous;
	ObjectChunk<T> *next;

private:
	int obj_count;
	int free_count;
	int free_index;
	T *p_obj;
	bool *free_array;
	int obj_size;
};

template<typename T>
class ObjectPool
{
public:
	ObjectPool();
	ObjectPool(int chunk_size);
	~ObjectPool();
	T* NewObject();
	bool DeleteObject(T *obj);
	void ShowCount();

private:
	ObjectChunk<T> *head;
	int chunk_size;
	int total_obj_count;
	int new_obj_count;

	void ClearChunck();
};

#endif // OBJECT_POOL_H
