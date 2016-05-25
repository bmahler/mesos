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

#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <process/clock.hpp>
#include <process/future.hpp>
#include <process/gtest.hpp>
#include <process/limiter.hpp>

#include <stout/duration.hpp>
#include <stout/nothing.hpp>

using process::Clock;
using process::Future;
using process::RateLimiter;


TEST(LimiterTest, Acquire)
{
  int permits = 2;
  Duration duration = Milliseconds(5);

  RateLimiter limiter(permits, duration);
  Milliseconds interval = duration / permits;

  Future<Nothing> acquire = limiter.acquire();

  AWAIT_READY(acquire);
}
