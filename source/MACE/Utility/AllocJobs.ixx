namespace MACE::Utility {

template<std::integral Job_t, std::integral Worker_t>
std::vector<Job_t> AllocJobs(Job_t nJobs, Worker_t nWorkers) {
    const auto commonJobs = nJobs / nWorkers;
    const auto remainJobs = nJobs - commonJobs * nWorkers;
    std::vector<Job_t> workerJobs(nWorkers, commonJobs);
    for (std::remove_const_t<decltype(remainJobs)> i = 0; i < remainJobs; ++i) {
        ++workerJobs[i];
    }
    return workerJobs;
}

} // namespace MACE::Utility