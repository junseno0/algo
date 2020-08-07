#include <stdlib.h>
#include <stdio.h>

typedef struct Demux_t Demux;

struct Demux_t {
    const char* name;
	//ops 可以集合成一个struct ops_t结构体，可以视作一个table虚表
    void (*open)(Demux* d);
    void (*close)(Demux* d);
    void (*probe)(Demux* d);
    void (*read)(Demux* d);
};

void _aac_open(Demux* d) { printf("kay: aac open.\n");};
void _aac_close(Demux* d) {printf("kay: aac close.\n");};
void _aac_probe(Demux* d) {printf("kay: aac probe.\n");};
void _aac_read(Demux* d) {printf("kay: aac read.\n");};

Demux aac_demux = {
	.name = "aac_demux",
	.open = _aac_open,
	.close = _aac_close,
	.probe = _aac_probe,
	.read = _aac_read,
};

void demuxOpen(Demux* d) {
	return d->open(d);
}

void demuxClose(Demux* d) {
	return d->close(d);
}

void demuxProbe(Demux* d) {
	return d->probe(d);
}

void demuxRead(Demux* d) {
	return d->read(d);
}

Demux* createdemuxer(int demux_type) {
	(void) demux_type;
	//How to return a specific demuxer type
	return &aac_demux;
}

int main() {
	Demux* d = createdemuxer(0);
	printf("demux name %s\n", d->name);
	demuxOpen(d);
	demuxProbe(d);
	demuxRead(d);
	demuxClose(d);
    return 0;
}