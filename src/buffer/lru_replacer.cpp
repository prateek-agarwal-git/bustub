//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// lru_replacer.cpp
//
// Identification: src/buffer/lru_replacer.cpp
//
// Copyright (c) 2015-2019, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "buffer/lru_replacer.h"

namespace bustub {

LRUReplacer::LRUReplacer(size_t num_pages) { this->capacity = num_pages; }

LRUReplacer::~LRUReplacer() = default;

bool LRUReplacer::Victim(frame_id_t *frame_id) {
  if (this->frameIds.empty()) {
    return false;
  }
  *frame_id = this->frameIds.back();
  this->frameIds.pop_back();
  return true;
}

void LRUReplacer::Pin(frame_id_t frame_id) {
  // rmove frame_id from replacer if present
  this->frameIds.remove(frame_id);
}

void LRUReplacer::Unpin(frame_id_t frame_id) {
  bool found = false;
  for (auto &frameId : this->frameIds) {
    if (frameId == frame_id) {
      found = true;
      break;
    }
  }
  // this->frameIds.remove(frame_id);
  if (!found) {
    if (this->frameIds.size() == this->capacity) {
      this->frameIds.pop_back();
    }
    this->frameIds.push_front(frame_id);
  }
}

size_t LRUReplacer::Size() { return this->frameIds.size(); }

}  // namespace bustub
