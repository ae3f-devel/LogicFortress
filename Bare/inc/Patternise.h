#define __Patternise(mem, el, count, size_t)  for(size_t i = 0; i < (count); i++) { (mem)[i] = el; }
#define __Zero(mem, count, size_t)  __Patternise(mem, 0, count, size_t)