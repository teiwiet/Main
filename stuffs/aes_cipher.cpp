#include <iostream>
#include <string>
#include <iomanip>
#include <crypto++/aes.h>
#include <crypto++/hex.h>
#include <crypto++/modes.h>
#include <crypto++/filters.h>

int main() {
    using namespace CryptoPP;

    // Khóa bí mật (key) và IV (Initialization Vector)
    byte key[AES::DEFAULT_KEYLENGTH] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 
                                        0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
    byte iv[AES::BLOCKSIZE] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                               0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};

    // Chuỗi cần mã hóa
    std::string plainText = "Hello, AES Encryption!";
    std::string cipherText, decryptedText;

    try {
        // Mã hóa AES (CBC Mode)
        CBC_Mode<AES>::Encryption encryption;
        encryption.SetKeyWithIV(key, sizeof(key), iv);

        StringSource encryptor(plainText, true,
            new StreamTransformationFilter(encryption,
                new StringSink(cipherText)
            )
        );

        // Giải mã AES (CBC Mode)
        CBC_Mode<AES>::Decryption decryption;
        decryption.SetKeyWithIV(key, sizeof(key), iv);

        StringSource decryptor(cipherText, true,
            new StreamTransformationFilter(decryption,
                new StringSink(decryptedText)
            )
        );

        // Xuất kết quả
        std::cout << "Plaintext: " << plainText << std::endl;

        // In ciphertext dưới dạng Hex
        std::string encodedCipherText;
        StringSource(cipherText, true,
            new HexEncoder(
                new StringSink(encodedCipherText)
            )
        );
        std::cout << "Ciphertext (Hex): " << encodedCipherText << std::endl;

        std::cout << "Decrypted Text: " << decryptedText << std::endl;
    }
    catch (const CryptoPP::Exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
