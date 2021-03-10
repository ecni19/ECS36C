#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "multimap.h"

// Task class
class Task {
 private:
  char ID;
  unsigned int tick_st;
  unsigned int tick_dur;
  unsigned int runtime;
  unsigned int v_runtime;

 public:
  Task(char c, unsigned int ts, unsigned int td) :
    ID(c), tick_st(ts), tick_dur(td), runtime(0) {}

  void IncRT() { runtime++; }
  void IncVRT() { v_runtime++; }
  void SetVRT(unsigned int v) { v_runtime = v; }
  char id() { return ID; }
  unsigned int start() { return tick_st; }
  unsigned int duration() { return tick_dur; }
  unsigned int rt() { return runtime; }
  unsigned int vrt() { return v_runtime; }
};

// Schedule class for tasks
class Schedule {
 private:
  unsigned int min_vruntime = 0;
 public:
  Multimap<int, Task*> mmap;

  Schedule() = default;
  void SetMinVRT(unsigned int mvrt) { min_vruntime = mvrt; }
  unsigned int MinVRT() { return min_vruntime; }
};

void AddTask(std::vector<Task*> &v, unsigned int &ticks, Schedule &s) {
  while (ticks == v.back()->start()) {
    Task* task = v.back();
    task->SetVRT(s.MinVRT());
    s.mmap.Insert(task->vrt(), task);
    v.pop_back();
    if (v.empty())
      break;
  }
}

// process and print the tasks
void ProcessTask(std::vector<Task*> &v) {
  // create an empty Schedule
  Schedule s;
  unsigned int ticks = 0;
  // assigned to nullptr until timeline receives items
  Task* curr_task = nullptr;

  while (s.mmap.Size() || v.size()) {
    // add items if possible
    if (ticks == 15)
      exit(0);
    // if tick is at a task's starting tick
    if (v.size() && ticks == v.back()->start()) {
      AddTask(v, ticks, s);
    }
    // if no tasks to run
    if (!s.mmap.Size()) {
        std::cout << ticks << " [" << s.mmap.Size() << "]: _\n";
        ticks++;
        continue;
    }

    // only initialize curr task if there's stuff
    if (s.mmap.Size()) {
      curr_task = s.mmap.Get(s.mmap.Min());
      s.SetMinVRT(curr_task->vrt());
    } else {
        curr_task = nullptr;
    }

    // vruntime exceeds minvruntime, move onto dif task if possible
    if (curr_task && curr_task->vrt() > s.MinVRT()) {
      unsigned int curr = s.mmap.Min();
      s.mmap.Remove(s.mmap.Min());
      unsigned int next = s.mmap.Min();
      // check if curr min = next min
      if (curr == next) {
        s.mmap.Insert(curr_task->vrt(), curr_task);
        curr_task = s.mmap.Get(curr);
        s.SetMinVRT(curr_task->vrt());
      } else {
        s.mmap.Insert(curr_task->vrt(), curr_task);
        curr_task = s.mmap.Get(s.mmap.Min());
        s.SetMinVRT(curr_task->vrt());
      }
    }
    // incrementing
    if (curr_task && curr_task->vrt() <= s.MinVRT()) {
      s.mmap.Remove(curr_task->vrt());

      curr_task->IncVRT();
      curr_task->IncRT();
      // checking if task is complete
      if (curr_task->rt() == curr_task->duration()) {
          s.mmap.Insert(curr_task->vrt(), curr_task);
          std::cout << ticks << " [" << s.mmap.Size() << "]: "
                    << curr_task->id() << "*\n";
          s.mmap.Remove(curr_task->vrt());
          delete curr_task;
      } else {
          s.mmap.Insert(curr_task->vrt(), curr_task);
          std::cout << ticks << " [" << s.mmap.Size() << "]: "
                    << curr_task->id() << "\n";
      }
    }
    ticks++;
  }
}

// comparator function for sorting
bool CompareTick(Task* t1, Task* t2) {
    if (t1->start() == t2->start())
      return t1->id() < t2->id();

    return (t1->start() < t2->start());
}

int main(int argc, char* argv[]) {
  std::vector<Task*> vect;

  // checking for correct program usage
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <task_file.dat>\n";
    exit(1);
  }

  std::fstream file;
  file.open(argv[1]);

  // checking for proper file
  if (!file.is_open()) {
    std::cerr << "Error: cannot open file " << argv[1] << '\n';
    exit(1);
  }

  char name;
  unsigned int tick_start;
  unsigned int tick_length;
  // read in file and push task objects into vector
  while (file >> name >> tick_start >> tick_length) {
    Task *t = new Task{name, tick_start, tick_length};
    vect.push_back(t);
  }

  // sort the vector in descending order.
  std::sort(vect.rbegin(), vect.rend(), CompareTick);

  // call the function that will process the tasks
  ProcessTask(vect);
}
