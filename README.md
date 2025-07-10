# 🧠 Adaptive Cache Replacement Project (ARC)

This project implements various cache replacement algorithms in C++, including:

- **LRU** (Least Recently Used)  
- **LFU** (Least Frequently Used)  
- **MRU** (Most Recently Used)  
- **ARC** (Adaptive Replacement Cache)

The ultimate goal is to explore and implement **ARC** as proposed in the original research paper:

> **"ARC: A Self-Tuning, Low Overhead Replacement Cache"**  
> by **Nimrod Megiddo** and **Dharmendra S. Modha**  
> 📄 [IEEE Computer, April 2004](https://theory.stanford.edu/~megiddo/pdf/IEEE_COMPUTER_0404.pdf)

---

## 📌 Objectives

This project was undertaken as part of the **core Data Structures and Algorithms course**, aimed at:

- Gaining hands-on experience with cache replacement policies  
- Understanding adaptive caching mechanisms  
- Benchmarking performance using real-world access patterns  

---

## ⚙️ Implementation Details

- 💻 Written in **C++**
- 🧱 Object-oriented design
- 🧪 Modular benchmarking for hit ratio and execution time
- 📂 Trace-based testing using disk I/O patterns

---

## 📊 Features

- Unified interface across all cache types (`get()`, `put()`)
- Faithful ARC implementation from the research paper
- Compatible with tab-separated MSR Cambridge trace files
- Easily switch between policies and cache sizes for comparison

---

## 📁 Trace File Support

Supports:

- MSR Cambridge Disk Traces  
- Custom `.lis` style traces (e.g., `block size ...` per line)

🔹 By default, only the **first 10,000 lines** of large traces are used for lightweight testing.

---

## 🚀 How to Run

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/arc-cache-cpp.git
   cd arc-cache-cpp
