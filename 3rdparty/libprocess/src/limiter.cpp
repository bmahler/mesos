// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License

#include <process/limiter.hpp>
#include <process/id.hpp>
#include <process/future.hpp>
#include <process/process.hpp>

#include <stout/duration.hpp>

namespace process {

class RateLimiterProcess : public Process<RateLimiterProcess>
{
public:
  RateLimiterProcess(int permits, const Duration& duration)
    : ProcessBase(ID::generate("__limiter__")) {}

  explicit RateLimiterProcess(double _permitsPerSecond)
    : ProcessBase(ID::generate("__limiter__")) {}

  // This will be run when the actor is spawned.
  virtual void initialize() {}

  // This will be run when the actor is terminated.
  virtual void finalize() {}

  Future<Nothing> acquire()
  {
    return Nothing();
  }

private:
  // Not copyable, not assignable.
  RateLimiterProcess(const RateLimiterProcess&);
  RateLimiterProcess& operator=(const RateLimiterProcess&);
};


RateLimiter::RateLimiter(int permits, const Duration& duration)
{
  process = new RateLimiterProcess(permits, duration);
  spawn(process);
}


RateLimiter::RateLimiter(double permitsPerSecond)
{
  process = new RateLimiterProcess(permitsPerSecond);
  spawn(process);
}


RateLimiter::~RateLimiter()
{
  terminate(process);
  wait(process);
  delete process;
}


Future<Nothing> RateLimiter::acquire() const
{
  return dispatch(process, &RateLimiterProcess::acquire);
}

} // namespace process {
