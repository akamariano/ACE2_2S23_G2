const redis = require("redis");
const chalk = require('chalk');

const redisClient = redis.createClient({
    password: '8EFmRwb0CzBa8yuiMLBnHlgIOjpv9MDs',
    socket: {
        host: 'redis-16132.c14.us-east-1-3.ec2.cloud.redislabs.com',
        port: 16132
    }
});

redisClient.on("error", (error) => {
    console.error("Redis - Error: ", error);
});

redisClient.connect();

redisClient.on("connect", () => {
    console.log(chalk.bold.green("Redis - Connected"));
});

module.exports = {
    redisClient
}
