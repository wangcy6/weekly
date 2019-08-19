

# Nervos 

1. 安装CKB
2. 启动CKB节点
3. 生成钱包
4. 挖矿
5. 查看结果

----------------------------------------------------------------------------------

中文：

https://www.hellobtc.com/kp/lc/wakuang/05/1793.html



**1:安装CKB**

<https://docs.nervos.org/getting-started/run-node>

**2: 启动CKB Node**







**3:生成钱包**

参考：https://github.com/rebase-network/ckb-wallet-generator 

root@work:~/wangchuanyi/money# ckb-cli wallet generate-key --privkey-path privkey
Put this config in < ckb.toml >:

[block_assembler]
code_hash = "0xf1951123466e4479842387a66fabfd6b65fc87fd84ae8e6cd3053edb27fff2fd"
args = ["0xaa2b3c6a901a3d50691adb3fd373864b988ce0cc"]

{
  "address": "ckt1q9gry5zg4g4nc65srg74q6g6mvlaxuuxfwvgecxv0cynw7",
  "lock_hash": "0x1ec02085bd69d8d33f9b0d9b3dd5d5c28311e7557c2058a6bf1564b88bfe8cee",
  "pubkey": "03271ff9902086120008ff89e637e8af7a2653f8f249c03c573f70e43112c13553"
}



cat privkey
bae1ace45b69cc3615393913c9a5775a80ffef486fd8271359aaf59c38009099
ckt1q9gry5zg4g4nc65srg74q6g6mvlaxuuxfwvgecxv0cynw7

