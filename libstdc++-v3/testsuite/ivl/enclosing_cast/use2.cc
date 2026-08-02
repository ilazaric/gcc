// { dg-do run { target c++26 } }
// { dg-options "-fsanitize=address,undefined" }

#include <enclosing_cast>
#include <string>
#include <format>
#include <vector>
#include <string_view>
#include <cassert>
#include <print>

struct erased;

struct person {
  std::string name;
  std::string address;
  std::string nickname;
};

struct car {
  int internal_id;
  std::string name;
};

struct session {
  int fd;
  int timeout;
  int permissions;
  std::string name;
};

struct container {
  std::vector<erased> elements;
  int length;
  std::string name;
  int capacity;
};

struct erased {
  int kind;
  std::string* name;
};

constexpr std::string extend(std::string_view sv) {
  std::string ret;
  for (auto c : sv) {
    if (c == '\n') ret += "\n    ";
    else ret += c;
  }
  return ret;
}

constexpr std::string stringify(erased e) {
  switch (e.kind) {
  case 0: {
    person& a = std::enclosing_cast<&person::name>(*e.name);
    assert(e.name == &a.name);
    return std::format("name={} --> person{{.address={}, .nickname={}}}", a.name, a.address, a.nickname);
  }
  case 1: {
    car& a = std::enclosing_cast<&car::name>(*e.name);
    assert(e.name == &a.name);
    return std::format("name={} --> car{{.internal_id={}}}", a.name, a.internal_id);
  }
  case 2: {
    session& a = std::enclosing_cast<&session::name>(*e.name);
    assert(e.name == &a.name);
    return std::format("name={} --> session{{.fd={}, .timeout={}, .permissions={}}}", a.name, a.fd, a.timeout, a.permissions);
  }
  case 3: {
    container& a = std::enclosing_cast<&container::name>(*e.name);
    assert(e.name == &a.name);
    std::string elstr;
    for (auto element : a.elements)
      elstr += "    " + extend(stringify(element)) + ",\n";
    return std::format("name={} --> container{{\n"
		       "  .length={},\n"
		       "  .capacity={},\n"
		       "  .elements=[\n"
		       "{}"
		       "  ]\n"
		       "}}", a.name, a.length, a.capacity, elstr);
  }
  default:
    assert(false);
  }
}

struct full_state {
  std::vector<person> persons;
  std::vector<car> cars;
  std::vector<session> sessions;
  std::vector<container> containers;
  std::vector<erased> eraseds;
};

[[gnu::noinline]]
constexpr full_state generate_state(int arg) {
  if (arg < 0) return {};
  full_state state;
  state.persons.emplace_back("john doe", "london", "jd");
  state.persons.emplace_back("jane doe", "paris", "dj");
  state.persons.emplace_back("alice", "boston", "A");
  state.persons.emplace_back("bob", "amsterdam", "B");
  state.cars.emplace_back(42, "toyota");
  state.cars.emplace_back(1337, "ferrari");
  state.cars.emplace_back(-1, "bicycle?");
  state.sessions.emplace_back(3, 100, 0777, "admin");
  state.sessions.emplace_back(4, 10, 0755, "post request");
  state.sessions.emplace_back(5, 5, 0555, "get request");
  state.sessions.emplace_back(6, 5, 0, "ddos");
  state.containers.emplace_back(std::vector{
      erased{0, &state.persons[1].name},
      erased{1, &state.cars[0].name},
      erased{0, &state.persons[3].name},
    }, 3, "parking lot occupancy", 33);
  state.containers.emplace_back(std::vector{
      erased{2, &state.sessions[3].name},
      erased{0, &state.persons[0].name},
      erased{1, &state.cars[2].name},
    }, 3, "bad actors", 3);
  state.containers.emplace_back();
  state.containers.back() = {std::vector{
      erased{3, &state.containers[1].name},
      erased{3, &state.containers[0].name},
    }, 2, "containers", 22};
  state.eraseds.emplace_back(0, &state.persons[2].name);
  state.eraseds.emplace_back(2, &state.sessions[0].name);
  state.eraseds.emplace_back(1, &state.cars[0].name);
  state.eraseds.emplace_back(2, &state.sessions[1].name);
  state.eraseds.emplace_back(1, &state.cars[1].name);
  state.eraseds.emplace_back(3, &state.containers[0].name);
  state.eraseds.emplace_back(3, &state.containers[1].name);
  state.eraseds.emplace_back(3, &state.containers[2].name);
  return state;
}

constexpr std::string stringify_all(const std::vector<erased>& eraseds) {
  std::string ret = "\n";
  for (auto e : eraseds) ret += stringify(e) + "\n";
  return ret;
}

constexpr std::string_view expected_output = R"(
name=alice --> person{.address=boston, .nickname=A}
name=admin --> session{.fd=3, .timeout=100, .permissions=511}
name=toyota --> car{.internal_id=42}
name=post request --> session{.fd=4, .timeout=10, .permissions=493}
name=ferrari --> car{.internal_id=1337}
name=parking lot occupancy --> container{
  .length=3,
  .capacity=33,
  .elements=[
    name=jane doe --> person{.address=paris, .nickname=dj},
    name=toyota --> car{.internal_id=42},
    name=bob --> person{.address=amsterdam, .nickname=B},
  ]
}
name=bad actors --> container{
  .length=3,
  .capacity=3,
  .elements=[
    name=ddos --> session{.fd=6, .timeout=5, .permissions=0},
    name=john doe --> person{.address=london, .nickname=jd},
    name=bicycle? --> car{.internal_id=-1},
  ]
}
name=containers --> container{
  .length=2,
  .capacity=22,
  .elements=[
    name=bad actors --> container{
      .length=3,
      .capacity=3,
      .elements=[
        name=ddos --> session{.fd=6, .timeout=5, .permissions=0},
        name=john doe --> person{.address=london, .nickname=jd},
        name=bicycle? --> car{.internal_id=-1},
      ]
    },
    name=parking lot occupancy --> container{
      .length=3,
      .capacity=33,
      .elements=[
        name=jane doe --> person{.address=paris, .nickname=dj},
        name=toyota --> car{.internal_id=42},
        name=bob --> person{.address=amsterdam, .nickname=B},
      ]
    },
  ]
}
)";

static_assert(stringify_all(generate_state(0).eraseds) == expected_output);

int main(int argc, char** /* argv */) {
  full_state state = generate_state(argc);
  std::string output = stringify_all(state.eraseds);
  assert(output == expected_output);
}
