#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class Channel {
public:
    Channel() = default;

    // 阻塞地将消息放入通道
    void Send(const T& message) {
        std::unique_lock<std::mutex> lock(mutex_);
        queue_.push(message);
        cond_var_.notify_one();  // 通知接收者有新消息
    }

    // 阻塞地接收消息
    T Receive() {
        std::unique_lock<std::mutex> lock(mutex_);
        cond_var_.wait(lock, [this]() { return !queue_.empty(); });  // 等待直到队列有消息
        T message = queue_.front();
        queue_.pop();
        return message;
    }

private:
    std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable cond_var_;
};
