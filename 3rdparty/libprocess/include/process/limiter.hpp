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

#ifndef __PROCESS_LIMITER_HPP__
#define __PROCESS_LIMITER_HPP__

#include <process/dispatch.hpp>
#include <process/future.hpp>

#include <stout/duration.hpp>
#include <stout/nothing.hpp>

namespace process {

// Forward declaration.
class RateLimiterProcess;

// Provides an abstraction that rate limits the number of "permits"
// that can be acquired over some duration.
class RateLimiter
{
public:
  RateLimiter(int permits, const Duration& duration);
  explicit RateLimiter(double permitsPerSecond);
  virtual ~RateLimiter();

  // Returns a future that becomes ready when the permit is acquired.
  // Discarding this future cancels this acquisition.
  virtual Future<Nothing> acquire() const;

private:
  // Not copyable, not assignable.
  RateLimiter(const RateLimiter&);
  RateLimiter& operator=(const RateLimiter&);

  RateLimiterProcess* process;
};

} // namespace process {

#endif // __PROCESS_LIMITER_HPP__
