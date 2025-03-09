#include "RSAEncryption.hpp"


RSAEncryption::RSAEncryption()
{
    OpenSSL_add_all_algorithms();
}

void RSAEncryption::GenerateKeys()
{
    //Генерируем ключи RSA
    RSA* rsa = RSA_generate_key(2048, RSA_F4, NULL, NULL);
    // Переводим публичный ключ в формат PEM, из него уже можно перевести в строчный
    BIO* publicKeyBio = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPublicKey(publicKeyBio, rsa);
    char* publicKeyBuffer;
    long publicKeyLength = BIO_get_mem_data(publicKeyBio, &publicKeyBuffer);
    public_key = std::string(publicKeyBuffer, publicKeyLength);
    BIO_free(publicKeyBio);
    // Переводим приватный ключ в формат PEM, из него уже можно перевести в строчный
    BIO* privateKeyBio = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPrivateKey(privateKeyBio, rsa, NULL, NULL, 0, NULL, NULL);
    char* privateKeyBuffer;
    long privateKeyLength = BIO_get_mem_data(privateKeyBio, &privateKeyBuffer);
    private_key = std::string(privateKeyBuffer, privateKeyLength);
    BIO_free(privateKeyBio);
    // Освобождаем контекст
    RSA_free(rsa);
}

std::string RSAEncryption::GetPublicKey()
{
    return public_key;
}

std::string RSAEncryption::GetPrivateKey()
{
    return private_key;
}