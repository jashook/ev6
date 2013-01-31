#include <iostream>
#include <queue>

#include "brokered_queue.hpp"
#include "hr_timer.hpp"
#include "write.hpp"
#include "read.hpp"
#include "vector.hpp"
#include "file_functor.hpp"
#include "directory.hpp"

#include "array.hpp"

#include "progress_bar.hpp"
#include "fr_process.hpp"
#include "lock.hpp"
#include "lock_handle.hpp"

void reimplemented_queue()
{
   ev4::hr_timer timer;

   ev4::mts::brokered_queue<int>* _Queue = new ev4::mts::brokered_queue<int>();

   timer.start();

   ev4::mts::write w;
   ev4::mts::read r;

   w.start(w, _Queue);
   r.start(r, _Queue);

   w.join();
   r.join();

   timer.stop();

   std::cout << timer.duration_as_milliseconds() << std::endl;
}

void standard_queue()
{
   ev4::hr_timer timer;

   std::pair< std::queue<int>*, ev4::mts::lock*>* _Pair = new std::pair< std::queue<int>*, ev4::mts::lock*>(new std::queue<int>(), new ev4::mts::lock());

   timer.start();

   ev4::mts::write w;
   ev4::mts::read r;

   w.start(w, _Pair);
   r.start(r, _Pair);

   w.join();
   r.join();

   timer.stop();

   std::cout << timer.duration_as_milliseconds() << std::endl;
}

int main()
{
   standard_queue();

   return 0;
}