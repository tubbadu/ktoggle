const clients = workspace.clientList();
for (var i = 0; i < clients.length; i++) {
  console.warn(">" + clients[i].windowId); //clients[i].resourceClass, clients[i].minimized, clients[i].active, 
}