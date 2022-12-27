#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>


class DiskContent {
 public:
  DiskContent(const std::string& name, size_t size) : name{name}, size{size} {}

  virtual bool isDir() = 0;

  size_t getSize() const { return this->size; }
  std::string getName() const { return this->name; }
  void setName(const std::string& name) { this->name = name; }

 protected:
  size_t size;
  std::string name;
};


class File : public DiskContent {
 public:
  File(const std::string& name, size_t size) : DiskContent(name, size) {}

  virtual bool isDir() override { return false; }
};


class Directory : public DiskContent {
 public:
  static const size_t diskSpaceTotal      = 70'000'000;
  static const size_t diskSpaceForUpgrade = 30'000'000;

  Directory(const std::string& name) : DiskContent(name, 0), parent(*this) {}
  Directory(const std::string& name, Directory& parent) : DiskContent(name, 0), parent(parent) {}

  Directory& getParent() { return this->parent; }
  const std::vector<DiskContent*>& getContent() const { return this->content; }

  Directory* findDir(const std::string& name) const {
    // Find Directory by name
    auto it = std::find_if(this->content.begin(), this->content.end(),
                           [&](DiskContent* dc) { return dc->isDir() && (dc->getName() == name); });

    if (it == this->content.end())
      throw std::runtime_error("Directory " + name + " not found!");

    return dynamic_cast<Directory*>(*it);
  }


  void add(DiskContent& diskContent) {
    this->content.push_back(&diskContent);
    this->size += diskContent.getSize();

    if (&this->parent == this)
      return;

    // also update size of parents
    Directory* parent = &this->parent;
    while (parent != &parent->getParent()) {
      parent->size += diskContent.getSize();
      parent = &parent->getParent();
    }
    parent->size += diskContent.getSize();
  }

  // Does not keep order in content vector
  bool deleteDiskContent(const std::string& contentName) {
    for (size_t i = 0; i < this->content.size(); ++i) {
      if (this->content[i]->getName() == contentName) {
        std::swap(content[i], content.back());
        this->size -= content.back()->getSize();
        delete content.back();
        this->content.pop_back();
        return true;
      }
    }
    return false;
  }

  void ls(bool recursive = false) {
    if (this->content.empty())
      return;

    std::cout << this->name;

    if (recursive) {
      std::cout << std::endl;
      printDirectoryContent();

    } else {
      std::cout << ": ";
      for (DiskContent* dc : content)
        std::cout << dc->getName() << ' ';
      std::cout << std::endl;
    }
  }

  size_t calcFreeSpace() {
    // return -1 if not called on root
    if (&this->parent != this)
      return -1;

    return diskSpaceTotal - this->getSize();
  }

  bool hasEnoughSpace() {
    if (&this->parent != this)
      return -1;

    return calcFreeSpace() >= this->diskSpaceForUpgrade;
  }

  virtual bool isDir() override { return true; }

 private:
  Directory& parent;
  std::vector<DiskContent*> content;

  void printDirectoryContent(int indentation = 2) {
    for (DiskContent* dc : content) {
      for (int i = 0; i < indentation; ++i)
        std::cout << " ";

      std::cout << dc->getName() << ' ' << dc->getSize() << std::endl;
      if (dc->isDir())
        ((Directory*)dc)->printDirectoryContent(indentation + 2);
    }
  }
};