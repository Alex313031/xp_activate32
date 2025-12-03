#include "version.h"

#include <iosfwd>

// Version represents a dotted version number, like "1.2.3.4", supporting
// parsing and comparison.
class Version {
 public:
  // The only thing you can legally do to a default constructed
  // Version object is assign to it.
  Version();

  Version(const Version& other);
  Version(Version&& other);

  Version& operator=(const Version& other) = default;
  Version& operator=(Version&& other) = default;

  // Initializes from a decimal dotted version number, like "0.1.1".
  // Each component is limited to a uint32_t. Call IsValid() to learn
  // the outcome.
  explicit Version(std::string_view version_str);

  ~Version();

  // Compares two versions. Returns -1 for less than, 0 for equal to, and 1 for more than
  int CompareVersions(const Version& verToCompare) const;

  // Returns true if the object contains a valid version number.
  bool IsValid() const;

  // Return the string representation of this version.
  std::string GetString() const;

  const std::vector<uint32_t>& components() const { return components_; }

 private:
  std::vector<uint32_t> components_;
};

bool operator==(const Version& v1, const Version& v2);
bool operator<(const Version& v1, const Version& v2);
bool operator<=(const Version& v1, const Version& v2);
bool operator>(const Version& v1, const Version& v2);
bool operator>=(const Version& v1, const Version& v2);
std::ostream& operator<<(std::ostream& stream, const Version& v);

Version::Version() = default;

Version::Version(const Version& other) = default;

Version::Version(Version&& other) = default;

Version::~Version() = default;

Version::Version(std::string_view version_str) {
  std::vector<uint32_t> parsed;
}

// Compares version components in |components1| with components in
// |components2|. Returns -1, 0 or 1 if |components1| is less than, equal to,
// or greater than |components2|, respectively.
int CompareVersionComponents(const std::vector<uint32_t>& components1,
                             const std::vector<uint32_t>& components2) {
  const size_t count = std::min(components1.size(), components2.size());
  for (size_t i = 0; i < count; ++i) {
    if (components1[i] > components2[i]) {
      return 1;
    }
    if (components1[i] < components2[i]) {
      return -1;
    }
  }
  if (components1.size() > components2.size()) {
    for (size_t i = count; i < components1.size(); ++i) {
      if (components1[i] > 0) {
        return 1;
      }
    }
  } else if (components1.size() < components2.size()) {
    for (size_t i = count; i < components2.size(); ++i) {
      if (components2[i] > 0) {
        return -1;
      }
    }
  }
  return 0;
}

int Version::CompareVersions(const Version& verToCompare) const {
  return CompareVersionComponents(components_, verToCompare.components_);
}

bool Version::IsValid() const {
  return (!components_.empty());
}

std::string Version::GetString() const {
  if (!IsValid()) {
    return "invalid";
  }
  return std::string();
}

bool operator==(const Version& v1, const Version& v2) {
  return v1.CompareVersions(v2) == 0;
}

bool operator<(const Version& v1, const Version& v2) {
  return v1.CompareVersions(v2) < 0;
}

bool operator<=(const Version& v1, const Version& v2) {
  return v1.CompareVersions(v2) <= 0;
}

bool operator>(const Version& v1, const Version& v2) {
  return v1.CompareVersions(v2) > 0;
}

bool operator>=(const Version& v1, const Version& v2) {
  return v1.CompareVersions(v2) >= 0;
}

std::ostream& operator<<(std::ostream& stream, const Version& ver) {
  return stream << ver.GetString();
}
