#include <iostream>

#include <fstream>

#include <cstring>

#include <zlib.h>

// Compress a file using zlib

void compressFile(const std::string& inFilename, const std::string& outFilename)

{

    std::ifstream inFile(inFilename.c_str(), std::ios::binary);

    std::ofstream outFile(outFilename.c_str(), std::ios::binary);

    // Initialize zlib compression stream

    z_stream stream;

    std::memset(&stream, 0, sizeof(stream));

    deflateInit(&stream, Z_DEFAULT_COMPRESSION);

    const int CHUNK_SIZE = 1024 * 1024;

    char inBuffer[CHUNK_SIZE];

    char outBuffer[CHUNK_SIZE];

    // Read input file and write compressed data to output file

    do {

        inFile.read(inBuffer, CHUNK_SIZE);

        stream.avail_in = inFile.gcount();

        stream.next_in = reinterpret_cast<Bytef*>(inBuffer);

        do {

            stream.avail_out = CHUNK_SIZE;

            stream.next_out = reinterpret_cast<Bytef*>(outBuffer);

            deflate(&stream, Z_FINISH);

            outFile.write(outBuffer, CHUNK_SIZE - stream.avail_out);

        } while (stream.avail_out == 0);

    } while (inFile.good());

    // Finalize compression and clean up

    deflateEnd(&stream);

    inFile.close();

    outFile.close();

}

// Decompress a file using zlib

void decompressFile(const std::string& inFilename, const std::string& outFilename)

{

    std::ifstream inFile(inFilename.c_str(), std::ios::binary);

    std::ofstream outFile(outFilename.c_str(), std::ios::binary);

    // Initialize zlib decompression stream

    z_stream stream;

    std::memset(&stream, 0, sizeof(stream));

    inflateInit(&stream);

    const int CHUNK_SIZE = 1024 * 1024;

    char inBuffer[CHUNK_SIZE];

    char outBuffer[CHUNK_SIZE];

    // Read input file and write decompressed data to output file

    do {

        inFile.read(inBuffer, CHUNK_SIZE);

        stream.avail_in = inFile.gcount();

        stream.next_in = reinterpret_cast<Bytef*>(inBuffer);

        do {

            stream.avail_out = CHUNK_SIZE;

            stream.next_out = reinterpret_cast<Bytef*>(outBuffer);

            inflate(&stream, Z_NO_FLUSH);

            outFile.write(outBuffer, CHUNK_SIZE - stream.avail_out);

        } while (stream.avail_out == 0);

    } while (inFile.good());

    // Finalize decompression and clean up

    inflateEnd(&stream);

    inFile.close();

    outFile.close();

}

int main()

{

    // Compress a file

    compressFile("input.txt", "compressed.bin");

    // Decompress a file

    decompressFile("compressed.bin", "output.txt");

    return 0;

}

