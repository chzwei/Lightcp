#ifndef OBJECT_POOL_H
#define OBJECT_POOL_H

template<typename T>
class ObjectChunk
{
public:
	ObjectChunk();
	ObjectChunk(int size);
	~ObjectChunk();
	T* new_object();
	bool delete_object(T *obj);
	bool is_inchunk(T *obj);
	bool isfull();
	bool isempty();

	ObjectChunk<T> *previous;
	ObjectChunk<T> *next;

private:
	int obj_size;
	int free_size;
	int free_index;
	T *p_obj;
	bool *free_array;
};

template<typename T>
class ObjectPool
{
public:
	ObjectPool();
	ObjectPool(int chunk_size);
	~ObjectPool();
	T* new_object();
	bool delete_object(T *obj);

private:
	ObjectChunk<T> *head;
	int chunk_size;
};

#endif // OBJECT_POOL_H
