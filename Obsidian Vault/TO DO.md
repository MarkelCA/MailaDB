# To do
- [ ] Add indexing.
    - Add an indexing algorithm. For example:
        - In memory hash-index to keep byte offsets
        - LSM-Tree
        - B+ Tree
    - To start the Byte-offset option will be used
- [ ] Delete function (tombstones)
- [ ] Format the command output and use the quotes properly
    - [ ] change the `Command not valid` output to remove quotes
    - [ ] Fix the quotes in the list function
- [ ] cli tool like `mysql` instead of using `telnet`
- [ ] Implement a type system like Redis
- [ ] Add log compaction
- [ ] Add users & permissions
- [ ] Might be interesting to use a documentation generator as [Docusaurus](https://docusaurus.io/)
- [ ] Take inspiration from the Redis cli(https://try.redis.io/)
- [ ] Abstract the storage format and the indexing algorithm to add flexibility

---
# Done

- [X] Make the storage file configurable
- [X] Use a thread for each client
- [X] `list` command
- [X] Optimize stored space. 
    - Is always stored 4 bytes for the key lenght, even if there aren't used. [[optimizations/Binary Encoding|Binary Encoding]]]
- [X] Add a network adapter. (Run through server connection instead of local cli)
