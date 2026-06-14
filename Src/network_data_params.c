/**
  ******************************************************************************
  * @file    network_data_params.c
  * @author  AST Embedded Analytics Research Platform
  * @date    2026-06-03T08:19:20+0800
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */

#include "network_data_params.h"


/**  Activations Section  ****************************************************/
ai_handle g_network_activations_table[1 + 2] = {
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
  AI_HANDLE_PTR(NULL),
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
};




/**  Weights Section  ********************************************************/
AI_ALIGNED(32)
const ai_u64 s_network_weights_array_u64[122] = {
  0x3e8fa1e8beab618cU, 0xbf03ab4dbedb20beU, 0xbbca5c09beaf248aU, 0x3f2d593e3f7a3ae9U,
  0xbeabd1043dd55d8cU, 0x3f59b18c3f16b76fU, 0x3e314940be2473e0U, 0xbdaac72c3db81c75U,
  0xbcae0db6bf10283fU, 0xbf4379583d09dafaU, 0x3c7faedfbf1b1c0aU, 0xbeae8cf5bef363e4U,
  0x3e81b0ecbf071d4dU, 0xbeccf8ca3db6d7a1U, 0xbec86373beb6a44cU, 0xbeae1dd5be8d4b19U,
  0x3f02e4c9be4eef20U, 0xbf07ab10bf43c528U, 0x3efdee373e8cdcd9U, 0x3f0d322a3f18b056U,
  0x3f04ed0d3ea4a7d7U, 0xbd95a49dbf23e032U, 0xbf123281bc8c8a71U, 0xbd3b8bb73f0d98a3U,
  0x3e93a5bbbe9ea1feU, 0x3f43b82a3f146d7cU, 0x3d72ab53bea1411eU, 0xbeea1fabbdf33d39U,
  0xbead5846bebd03d6U, 0x3e4f9dc2beceea8cU, 0xbf19ea863e12fc28U, 0x3e809287becc1515U,
  0xbe82dbeb3e12bb82U, 0x3d6ebd82be755153U, 0x3c4498983d5dcd8bU, 0x3c1ae7523f1efb42U,
  0x3e91e4a43e71e11aU, 0x3f00a6783f2575fbU, 0xbc1ebb40be07ce60U, 0x3ef3fc52bd449b77U,
  0x3f5d36573eae0f0aU, 0xbefc4c373e036239U, 0xbefa4e3bbea48649U, 0x3ef4e62cbef44818U,
  0x3e9a6e143e8b8632U, 0x3ecebf51bedf565fU, 0x3e9e0f4bbaa6d66bU, 0xbe95c3413ef62c2aU,
  0xbf5863fd3f44c33cU, 0xbe115334beea452bU, 0x3e721b663ead7d29U, 0x3eed32b73f431e8fU,
  0x3e7dc431bd747dd2U, 0x3ea488f63f7f3562U, 0x3f23f108be4775fdU, 0x3f0781c2be379083U,
  0x3ded754dbe884bb0U, 0x3e4422403e7884ccU, 0x3e905330bedcf4c5U, 0xbeaa76053e97db82U,
  0xbe07b669bead7e04U, 0xbeda2a49bf05a395U, 0x3ecbad8abe294dceU, 0x3e54f7e23ebdec83U,
  0x3f071877bf1fbb87U, 0xbe8e988a3f2f408cU, 0x3dd66bf6be0e674bU, 0xbd5da97dbf1d3d13U,
  0x3e4b0cbfbeff697fU, 0x3ee51977be96e24cU, 0xbd800d383f0d29d9U, 0x3eda6de63e73b998U,
  0xbee5326cbf25f761U, 0x3e3e26d1bea28419U, 0xbedd5a55be22d671U, 0xbe45d5f53f193abaU,
  0x3da7c3293d5b4f19U, 0x3f1c9b543f1a289eU, 0xbef0f193bf0a2136U, 0x3f2f39f03d2e2248U,
  0xbd009a94bf065627U, 0xbed500193e8061cdU, 0x3ea12928be95b754U, 0xbecae7f43efb441fU,
  0xbd9a1ef9bed7b0a2U, 0x3f2f4ad43edf8711U, 0x3e61a06d3e0fa0a6U, 0x3e9903c5be5c62caU,
  0x3eb930e48a86e321U, 0xbcacee55bf14cf42U, 0x3e8377abbd172f1bU, 0xbdde92173d06964eU,
  0x3db4c4cfbdfb04ceU, 0xbcd90ccabedc370eU, 0xbae95af53eabf837U, 0xbee4174c374df53cU,
  0x3d95e7703ef05be2U, 0xbe64a39c3f317f47U, 0x3f3f50b43e85c617U, 0x3dfd3e223e24980aU,
  0xbf19baf23f2d4dd1U, 0xbd83001b3f423bf5U, 0xbdd84a253e8bb28cU, 0xbe0253293ec8ad98U,
  0x3eea1b33be54ff40U, 0x3d2dc37bbdf98651U, 0x3ecbbfea3eeefb78U, 0xbe2875d9bdd37a09U,
  0x3f07d765be7952d3U, 0xbf883c0dbe209aa1U, 0xbf845c07bf87e4d6U, 0x3f5affd73eb3d33cU,
  0x3f721279bf5d26a2U, 0xbf19ecd03de296a3U, 0x3e9c0c263f9eed40U, 0xbf8e688bbf244d2bU,
  0xbef1fe123f103f6bU, 0x3f75b004bea21099U, 0xbd905018bf152974U, 0x3ece6f1fbf20b3caU,
  0x3e8458cebd35bcb1U, 0xbe69199cU,
};


ai_handle g_network_weights_table[1 + 2] = {
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
  AI_HANDLE_PTR(s_network_weights_array_u64),
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
};

