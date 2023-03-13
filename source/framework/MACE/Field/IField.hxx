#pragma once

#include <array>

namespace MACE::Field {

template<int Components>
class IField {
public:
    IField() = default;
    virtual ~IField() = default;

    IField(const IField&) = delete;
    IField& operator=(const IField&) = delete;
    bool operator==(const IField&) = delete;
    bool operator!=(const IField&) = delete;
    bool operator<(const IField&) = delete;
    bool operator<=(const IField&) = delete;
    bool operator>(const IField&) = delete;
    bool operator>=(const IField&) = delete;
    auto operator<=>(const IField&) = delete;

    std::array<double, Components> GetFieldValue(double x, double y, double z) = 0;
};

} // namespace MACE::Field
