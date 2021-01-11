from Hologram.CustomCloud import CustomCloud

credentials = None
send_host = "example.host.com"
send_port = 9877
hologram = CustomCloud(credentials,send_host,send_port,network='cellular')

print("version:", hologram.version, "type:", hologram.network_type)

result = hologram.sendMessage(b'hello')

print("Received:", result)
