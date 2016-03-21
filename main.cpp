// adapted from http://stackoverflow.com/questions/4306/what-is-the-best-way-to-create-a-sparse-array-in-c
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <unordered_map>
#include <QDebug>
#include <QElapsedTimer>

#define RAND_COUNT 10000000

class triple {
public:
    int x;
    int y;
    int z;
    bool operator<(const triple &other) const {
        if (x < other.x) return true;
        if (other.x < x) return false;
        if (y < other.y) return true;
        if (other.y < y) return false;
        return z < other.z;
    }
};

int something = 0;
void doSomething(int i) {
    something = i;
    //    printf(".");
}

void mapBench() {
    QElapsedTimer timer;
    timer.start();
    std::map<int,triple> data;
    triple point;
    int i;

    for (i = 0; i < RAND_COUNT; ++i) {
        point.x = i;
        point.y = rand();
        point.z = rand();
        //printf("%d %d %d %d\n", i, point.x, point.y, point.z);
        data[i] = point;
    }
    qDebug() << Q_FUNC_INFO << "creation: elapsed" << timer.elapsed();
    timer.restart();
    foreach (auto t, data) {
        if (t.second.x % 1000 == 0)
            doSomething(t.second.x);
    }
    qDebug() << "   foreach: elapsed" << timer.elapsed();
    timer.restart();
    for( auto it = data.begin(); it != data.end(); ++it ) {
        if (it->second.x % 1000 == 0)
            doSomething(it->second.x);
    }
    qDebug() << "   range-based for: elapsed" << timer.elapsed();

    timer.restart();
    for (i = 0; i < RAND_COUNT; ++i) {
        auto it = data.find(i);
        Q_ASSERT(it->second.x == i);
        if (it->second.x % 1000 == 0)
            doSomething(it->first);
    }
    qDebug() << "   find: elapsed" << timer.elapsed();
}

void unorderedMapBench() {
    QElapsedTimer timer;
    timer.start();
    std::unordered_map<int,triple> data;
    triple point;
    int i;

    for (i = 0; i < RAND_COUNT; ++i) {
        point.x = i;
        point.y = rand();
        point.z = rand();
        //printf("%d %d %d %d\n", i, point.x, point.y, point.z);
        data[i] = point;
    }
    qDebug() << Q_FUNC_INFO << "creation: elapsed" << timer.elapsed();
    timer.restart();
    foreach (auto t, data) {
        if (t.second.x % 1000 == 0)
            doSomething(t.second.x);
    }
    qDebug() << "   foreach: elapsed" << timer.elapsed();
    timer.restart();
    for( auto it = data.begin(); it != data.end(); ++it ) {
        if (it->second.x % 1000 == 0)
            doSomething(it->second.x);
    }
    qDebug() << "   range-based for: elapsed" << timer.elapsed();

    timer.restart();
    for (i = 0; i < RAND_COUNT; ++i) {
        auto it = data.find(i);
        Q_ASSERT(it->second.x == i);
        if (it->second.x % 1000 == 0)
            doSomething(it->first);
    }
    qDebug() << "   find: elapsed" << timer.elapsed();
}

void qHashBench() {
    QElapsedTimer timer;
    timer.start();
    QHash<int,triple> data;
    triple point;
    int i;

    for (i = 0; i < RAND_COUNT; ++i) {
        point.x = i;
        point.y = rand();
        point.z = rand();
        //printf("%d %d %d %d\n", i, point.x, point.y, point.z);
        data[i] = point;
    }
    qDebug() << Q_FUNC_INFO << "creation: elapsed" << timer.elapsed();
    timer.restart();
    foreach (const triple &t, data) {
        if (t.x % 1000 == 0)
            doSomething(t.x);
    }
    qDebug() << "   foreach: elapsed" << timer.elapsed();
#if QT_VERSION >= 0x050700
    timer.restart();
    foreach (const triple &t, qAsConst(data)) {
        if (t.x % 1000 == 0)
            doSomething(t.x);
    }
    qDebug() << "   qAsConst foreach: elapsed" << timer.elapsed();
#endif
    timer.restart();
    for( auto it = data.begin(); it != data.end(); ++it ) {
        if (it->x % 1000 == 0)
            doSomething(it->x);
    }
    qDebug() << "   range-based for: elapsed" << timer.elapsed();
#if QT_VERSION >= 0x050700
    timer.restart();
    for( auto it = qAsConst(data).begin(); it != qAsConst(data).end(); ++it ) {
        if (it->x % 1000 == 0)
            doSomething(it->x);
    }
    qDebug() << "   qAsConst range-based for: elapsed" << timer.elapsed();
#endif
    timer.restart();
    for (i = 0; i < RAND_COUNT; ++i) {
        auto it = data.find(i);
        Q_ASSERT(it.value().x == i);
        if (it->x % 1000 == 0)
            doSomething(it.value().x);
    }
    qDebug() << "   find: elapsed" << timer.elapsed();
}

void qMapBench() {
    QElapsedTimer timer;
    timer.start();
    QMap<int,triple> data;
    triple point;
    int i;

    for (i = 0; i < RAND_COUNT; ++i) {
        point.x = i;
        point.y = rand();
        point.z = rand();
        //printf("%d %d %d %d\n", i, point.x, point.y, point.z);
        data[i] = point;
    }
    qDebug() << Q_FUNC_INFO << "creation: elapsed" << timer.elapsed();
    timer.restart();
    foreach (const triple &t, data) {
        if (t.x % 1000 == 0)
            doSomething(t.x);
    }
#if QT_VERSION >= 0x050700
    qDebug() << "   foreach: elapsed" << timer.elapsed();
    timer.restart();
    foreach (const triple &t, qAsConst(data)) {
        if (t.x % 1000 == 0)
            doSomething(t.x);
    }
    qDebug() << "   qAsConst foreach: elapsed" << timer.elapsed();
#endif
    timer.restart();
    for( auto it = data.begin(); it != data.end(); ++it ) {
        if (it->x % 1000 == 0)
            doSomething(it->x);
    }
    qDebug() << "   range-based for: elapsed" << timer.elapsed();
#if QT_VERSION >= 0x050700
    timer.restart();
    for( auto it = qAsConst(data).begin(); it != qAsConst(data).end(); ++it ) {
        if (it->x % 1000 == 0)
            doSomething(it->x);
    }
    qDebug() << "   qAsConst range-based for: elapsed" << timer.elapsed();
#endif

    timer.restart();
    for (i = 0; i < RAND_COUNT; ++i) {
        auto it = data.find(i);
        Q_ASSERT(it.value().x == i);
        if (it->x % 1000 == 0)
            doSomething(it.value().x);
    }
    qDebug() << "   find: elapsed" << timer.elapsed();

    timer.restart();
    for (i = 0; i < RAND_COUNT; ++i) {
        auto val = data.value(i);
        if (val.x % 1000 == 0)
            doSomething(val.x);
    }
    qDebug() << "   value: elapsed" << timer.elapsed();
}

int main(int argc, char** argv)
{
    if (argc == 1 || !strcmp(argv[1], "map"))
        mapBench();
    if (argc == 1 || !strcmp(argv[1], "unorderedMap"))
        unorderedMapBench();
    if (argc == 1 || !strcmp(argv[1], "QHash"))
        qHashBench();
    if (argc == 1 || !strcmp(argv[1], "QMap"))
        qMapBench();
    return 0;
}
