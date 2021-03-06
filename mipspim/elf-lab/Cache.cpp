/*
 * DirectMappedCache.cpp
 *
 *  Created on: Oct 20, 2015
 *      Author: jbb
 */

#include "Cache.h"

#include "global.h"

Cache::Cache(unsigned logBlockSize_, unsigned logDepth_)
: logBlockSize(logBlockSize_),
  logDepth(logDepth_),
  accesses(0),
  hits(0),
  tagArray(new unsigned [1<<logDepth]),
  validArray(new bool [1<<logDepth])
{ }

Cache::~Cache() {
  delete tagArray;
  delete validArray;
}

bool Cache::checkHit(unsigned addr) {
	
	unsigned space = (1 << (logDepth))-1; //sets amount of space in cache
	unsigned tag = (addr >> logDepth + logBlockSize); //sets tag value
	int index = (addr >> logDepth) & space; //sets index with bitwise comparison
  	++accesses; //increases the number of accesses regardless of outcome

	if(tagArray[index] == tag && validArray[index]) { //if tag yields hit
 		++hits; //increment the number of hits, as this is a hit
 		return true;
	} else { //if tag does not yield hit
		validArray[index] = true; //sets array at this index to be valid
		tagArray[index] = tag; //sets tag array at this index to be t
		return false;
	}
}

void Cache::printStats() {
  printf("accesses = %u  hits = %u  hit rate = %f\n", accesses, hits, (float) hits/accesses);
}
