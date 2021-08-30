# openssl-demo
基于openssl的TLS双向认证demo

## usage
```
make gen # 生成密钥；第一次出现 pass phrase 时输入 server，第二次输入 client
make build
make run-server
make run-client
```