//
//  KDB3Node.h
//  KeePass2
//
//  Created by Qiang Yu on 2/12/10.
//  Copyright 2010 Qiang Yu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Kdb.h"
#import "UUID.h"

#define KDB3_SIG1 (0x9AA2D903)
#define KDB3_SIG2 (0xB54BFB65)

#define KDB3_VER  (0x00030004)
#define KDB3_HEADER_SIZE (124)

#define FLAG_SHA2     1
#define FLAG_RIJNDAEL 2
#define FLAG_ARCFOUR  4
#define FLAG_TWOFISH  8

typedef struct {
	uint32_t signature1;
	uint32_t signature2;
	uint32_t flags;
	uint32_t version;

	uint8_t masterSeed[16];
	uint8_t encryptionIv[16];

	uint32_t groups;
	uint32_t entries;

	uint8_t contentsHash[32];

	uint8_t masterSeed2[32];
	uint32_t keyEncRounds;
} kdb3_header_t;

@interface Kdb3Group : KdbGroup {
    uint32_t groupId;
    uint32_t flags;
    NSMutableArray *metaEntries;
}

@property(nonatomic, assign) uint32_t groupId;
@property(nonatomic, assign) uint32_t flags;
@property(nonatomic, readonly) NSArray *metaEntries;

@end


@interface Kdb3Entry : KdbEntry {
    UUID *uuid;
    NSString *binaryDesc;
    NSData *binary;
}

@property(nonatomic, retain) UUID *uuid;
@property(nonatomic, copy) NSString *binaryDesc;
@property(nonatomic, retain) NSData *binary;

- (BOOL)isMeta;

@end


@interface Kdb3Tree : KdbTree {
    uint32_t rounds;
}

@property(nonatomic, assign) uint32_t rounds;

- (id)init;

@end
