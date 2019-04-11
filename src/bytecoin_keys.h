#ifndef KEYS_H
#define KEYS_H

#include "bytecoin_crypto.h"

#define BYTECOIN_ADDRESS_BASE58_PREFIX          6       // legacy addresses start with "2"
#define BYTECOIN_ADDRESS_BASE58_PREFIX_AMETHYST 572238  // addresses start with "bcnZ", varintdata={0xce, 0xf6, 0x22}

void derive_from_seed_to_hash(const hash_t* seed, const void* buf, size_t len, hash_t* result);
void derive_from_seed_to_scalar(const hash_t* seed, const void* buf, size_t len, elliptic_curve_scalar_t* result);

void secret_key_to_public_key(const secret_key_t* secret_key, public_key_t* result);
void secret_keys_to_public_key(const secret_key_t* a, const secret_key_t* b, public_key_t* result);
void secret_keys_to_A_plus_sH(
        const secret_key_t* spend_secret_key,
        const secret_key_t* audit_key_base_secret_key,
        public_key_t* sH,
        public_key_t* A_plus_sH);

void generate_keyimage(const public_key_t* pub, const secret_key_t* sec, keyimage_t* result);
void generate_hd_secret_key(const secret_key_t* a0, const public_key_t* A_plus_sH, uint32_t index, secret_key_t* result);

void generate_output_secrets(
        const hash_t* output_det_key,
        secret_key_t* output_secret_scalar,
        elliptic_curve_point_t* output_secret_point,
        uint8_t* output_secret_address_type);

void linkable_derive_output_public_key(
        const secret_key_t* output_secret_scalar,
        const hash_t* tx_inputs_hash,
        uint32_t output_index,
        const public_key_t* address_s,
        const public_key_t* address_v,
        public_key_t* output_public_key,
        public_key_t* encrypted_output_secret);

void unlinkable_derive_output_public_key(
        const elliptic_curve_point_t* output_secret_point,
        const hash_t* tx_inputs_hash,
        uint32_t output_index,
        const public_key_t* address_s,
        const public_key_t* address_s_v,
        public_key_t* output_public_key,
        public_key_t* encrypted_output_secret);

//void generate_signature_H(
//        const hash_t* prefix_hash,
//        const public_key_t* sec_H,
//        const secret_key_t* sec,
//        signature_t* result);

void generate_proof_H(const secret_key_t* s, signature_t* result);

void encode_address(
        uint64_t prefix,
        const public_key_t* spend,
        const public_key_t* view,
        char* result,
        size_t result_len);

#endif // KEYS_H