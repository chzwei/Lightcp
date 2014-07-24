#include "ObjectPool.h"
#include <cstring>
#include <stdio.h>
using namespace std;

template<typename T>
ObjectChunk<T>::ObjectChunk(){

	previous = NULL;
	next = NULL;

	obj_size = 1000;
	free_size = obj_size;
	free_index = 0;
	p_obj = new T[obj_size];
	free_array = new bool[obj_size];
	memset(free_array, true, obj_size);
}

template<typename T>
ObjectChunk<T>::ObjectChunk(int size){

	previous = NULL;
	next = NULL;

	obj_size = size;
	free_size = obj_size;
	free_index = 0;
	p_obj = new T[obj_size];
	free_array = new bool[obj_size];
	memset(free_array, true, obj_size);
}

template<typename T>
ObjectChunk<T>::~ObjectChunk(){
	delete [] p_obj;
	delete [] free_array;
}

template<typename T>
T* ObjectChunk<T>::NewObject(){
	if(free_size == 0)
		return NULL;
	while(1){
		free_index = (free_index +1) % obj_size;
		if(free_array[free_index]){
			free_array[free_index] = false;
			free_size --;
			return &this->p_obj[free_index];
		}
	}
}

template<typename T>
bool ObjectChunk<T>::DeleteObject(T *obj){
	int obj_addr = (int)obj;	
	int p_obj_addr = (int)p_obj;
	int obj_index = obj_addr - p_obj_addr;
	obj_index /= sizeof(T);
	free_array[obj_index] = true;
	free_size ++;
	return true;
}

template<typename T>
bool ObjectChunk<T>::IsInchunk(T *obj){
	int obj_addr = (int)obj;
	int p_obj_addr = (int)p_obj;
	int obj_index = obj_addr - p_obj_addr;
	if(obj_index % sizeof(T)) false;
	obj_index /= sizeof(T);
	if(obj_index >= 0 && obj_index < obj_size){
		return true;
	}
	return false;	
}

template<typename T>
bool ObjectChunk<T>::IsFull(){
	return free_size == 0;
}

template<typename T>
bool ObjectChunk<T>::IsEmpty(){
	return obj_size == free_size;
}

template<typename T>
ObjectPool<T>::ObjectPool(){
	this->chunk_size = 1000;
	head = new ObjectChunk<T>();
}

template<typename T>
ObjectPool<T>::ObjectPool(int chunk_size){
	this->chunk_size = 10000;
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
T* ObjectPool<T>::new_object(){
	ObjectChunk<T> *tmp = head;
	while(tmp->next != NULL){
		if(!tmp->isfull()){
			return tmp->new_object();
		}
		tmp = tmp->next;
	}
	if(tmp->isfull()){
		ObjectChunk<T> *tmp_obj = new ObjectChunk<T>();
		tmp->next = tmp_obj;
		tmp = tmp_obj;
	}
	return tmp->new_object();
}

template<typename T>
bool ObjectPool<T>::delete_object(T *obj){
	ObjectChunk<T> *tmp = head;
	while(tmp->next != NULL) {
	    if(tmp->is_inchunk(obj)){
	    	tmp->delete_object(obj);
	    	return true;
	    }
	    tmp = tmp->next;
	}
	if(tmp->is_inchunk(obj)){
		tmp->delete_object(obj);
		return true;
	}else{
		return false;
	}
}