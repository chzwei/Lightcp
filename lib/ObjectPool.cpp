#include "ObjectPool.h"
#include <cstring>
#include <stdio.h>
using namespace std;

template<typename T>
ObjectChunk<T>::ObjectChunk(){

	previous = NULL;
	next = NULL;

	obj_size = sizeof(T);
	obj_count = 1000;
	free_count = obj_count;
	free_index = 0;
	p_obj = new T[obj_count];
	free_array = new bool[obj_count];
	memset(free_array, true, obj_count);
}

template<typename T>
ObjectChunk<T>::ObjectChunk(int size){

	previous = NULL;
	next = NULL;

	obj_size = sizeof(T);
	obj_count = size;
	free_count = obj_count;
	free_index = 0;
	p_obj = new T[obj_count];
	free_array = new bool[obj_count];
	memset(free_array, true, obj_count);
}

template<typename T>
ObjectChunk<T>::~ObjectChunk(){
	delete [] p_obj;
	delete [] free_array;
}

template<typename T>
T* ObjectChunk<T>::NewObject(){
	if(free_count == 0)
		return NULL;
	while(1){
		free_index = (free_index +1) % obj_count;
		if(free_array[free_index]){
			free_array[free_index] = false;
			free_count --;
			return &this->p_obj[free_index];
		}
	}
}

template<typename T>
bool ObjectChunk<T>::DeleteObject(T *obj){
	int obj_addr = (int)obj;	
	int p_obj_addr = (int)p_obj;
	int obj_index = (obj_addr - p_obj_addr)/obj_size;
	free_array[obj_index] = true;
	free_count ++;
	return true;
}

template<typename T>
bool ObjectChunk<T>::IsInchunk(T *obj){
	int obj_addr = (int)obj;
	int p_obj_addr = (int)p_obj;

	if( (obj_addr - p_obj_addr) % obj_size ) 
		return false;
	
	int obj_index = (obj_addr - p_obj_addr)/obj_size;
	if(obj_index >= 0 && obj_index < obj_count){
		return true;
	}
	return false;	
}

template<typename T>
bool ObjectChunk<T>::IsFull(){
	return free_count == 0;
}

template<typename T>
bool ObjectChunk<T>::IsEmpty(){
	return free_count == obj_count;
}

template<typename T>
ObjectPool<T>::ObjectPool(){
	chunk_size = 1000;
	total_obj_count = chunk_size;
	new_obj_count = 0;
	head = new ObjectChunk<T>();
}

template<typename T>
ObjectPool<T>::ObjectPool(int size){
	chunk_size = size;
	total_obj_count = chunk_size;
	new_obj_count = 0;
	head = new ObjectChunk<T>();
}

template<typename T>
ObjectPool<T>::~ObjectPool(){
	ObjectChunk<T> *tmp = head;
	while(head->next != NULL){
		tmp = head->next;
		delete head;
		head = tmp;
	}
	delete head;
}

template<typename T>
T* ObjectPool<T>::NewObject(){
	ObjectChunk<T> *tmp = head;
	while(tmp->next != NULL){
		if(!tmp->IsFull()){
			++ new_obj_count;
			return tmp->NewObject();
		}
		tmp = tmp->next;
	}
	if(tmp->IsFull()){
		ObjectChunk<T> *tmp_chunk = new ObjectChunk<T>();
		total_obj_count += chunk_size;
		tmp->next = tmp_chunk;
		tmp = tmp_chunk;
	}
	++ new_obj_count;
	return tmp->NewObject();
}

template<typename T>
bool ObjectPool<T>::DeleteObject(T *obj){
	ObjectChunk<T> *tmp = head;
	while(tmp != NULL) {
	    if(tmp->IsInchunk(obj)){
	    	tmp->DeleteObject(obj);
	    	-- new_obj_count;
	    	if(new_obj_count*2 < total_obj_count){
				ClearChunck();
			}
	    	return true;
	    }
	    tmp = tmp->next;
	}
	return false;
}

template<typename T>
void ObjectPool<T>::ClearChunck(){
	ObjectChunk<T> *tmp = head;
	ObjectChunk<T> *tmp_next = head->next;
	ObjectChunk<T> *del = NULL;

	while(tmp_next != NULL) {
	    if(tmp_next->IsEmpty()){
	    	del = tmp_next;
	    	tmp_next = tmp_next->next;
			tmp->next = tmp_next;
	    	delete del;
	    	del = NULL;
			total_obj_count -= chunk_size;
	    }else{
	    	tmp = tmp_next;
			tmp_next = tmp_next->next;
	    }
	}
}

template<typename T>
void ObjectPool<T>::ShowCount(){
	printf("used: %d \t total: %d\n", new_obj_count, total_obj_count);
}
