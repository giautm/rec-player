/*
 * stacked_task.h
 *
 *  Created on: 2 Feb 2015
 *      Author: Khanh Tran
 */

#ifndef STACKED_TASK_H_
#define STACKED_TASK_H_

#include <stack>

namespace tmg {

template<typename _Type, typename _PredPop, typename _Task,
    typename _Stack = std::stack<_Type> >
bool stackedTask(_Type init, _PredPop _predpop, _Task task) {
  _Stack stack;
  stack.push(init);

  bool cancel = false;
  while (!stack.empty() && !cancel) {
    auto& top = stack.top();
    if (_predpop(top)) {
      stack.pop();
    } else {
      bool pushToStack = false;
      _Type e = task(top, pushToStack, cancel);
      if (pushToStack) {
        stack.push(e);
      }
    }
  }

  return stack.empty();
}

} /* namespace tmg */

#endif /* STACKED_TASK_H_ */
