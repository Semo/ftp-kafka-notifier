#include <iostream>
#include <cstdio>
#include <cerrno>
#include <cstring>
#include <fstream>

extern "C" {
#include <librdkafka/rdkafka.h>
}

bool fexists(const char *filename) {
    std::ifstream ifile(filename);
    return (bool) ifile;
}

int main(int argc, char **argv) {

    rd_kafka_t *rk;         /* Producer instance handle */
    rd_kafka_topic_t *rkt;  /* Topic object */
    rd_kafka_conf_t *conf;  /* Temporary configuration object */
    char errstr[512];       /* librdkafka API error reporting buffer */
    char buf[512];          /* Message value temporary buffer */
    const char *brokers;    /* Argument: broker list */
    const char *topic;      /* Argument: topic to produce to */

    /*
     * Argument validation
     */
    if (argc != 3) {
        fprintf(stderr, "%% Usage: %s <broker> <topic>\n", argv[0]);
        return 1;
    }

    brokers = argv[1];
    topic = argv[2];

    /*
        * Create producer instance.
        *
        * NOTE: rd_kafka_new() takes ownership of the conf object
        *       and the application must not reference it again after
        *       this call.
        */
    rk = rd_kafka_new(RD_KAFKA_PRODUCER, conf, errstr, sizeof(errstr));
    if (!rk) {
        fprintf(stderr,
                "%% Failed to create new producer: %s\n", errstr);
        return 1;
    }

    if (!fexists(argv[1])) {
        fprintf(stderr,
                "%% Failed to rename file: %s\n", argv[1]);
        return 1;
    } else {
        rename(argv[1], argv[2]);
        std::cerr << "Renaming/Moving " << argv[1] << ": " << strerror(errno) << std::endl;
    }


    /* Destroy the producer instance */
    rd_kafka_destroy(rk);

    return 0;
}
