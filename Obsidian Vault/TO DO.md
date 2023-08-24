# To do
- [ ] Format the command output and use the quotes properly
    - [ ] change the `Command not valid` output to remove quotes
    - [ ] Fix the quotes in the list function
- [ ] Delete function (tombstones)
- [ ] cli tool like `mysql` instead of using `telnet`
- [ ] Use a thread for each request
- [ ] Implement a type system like Redis
    - Currently the only way to use the database it's through a cli. This isn't very useful.
- [ ] Add indexing.
    - Add an indexing algorithm. For example:
        - Byte-offset stored in memory for every key
        - LSM-Tree
        - B+ Tree
- [ ] Add log compaction
- [ ] Add users & permissions
- [ ] Might be interesting to use a documentation generator as [Docusaurus](https://docusaurus.io/)
- [ ] Take inspiration from the Redis cli(https://try.redis.io/)
- [ ] Abstract the storage format and the indexing algorithm to add flexibility

---
# Done

- [X] `list` command
- [X] Optimize stored space. 
    - Is always stored 4 bytes for the key lenght, even if there aren't used. [[optimizations/Binary Encoding|Binary Encoding]]]
- [X] Add a network adapter.
