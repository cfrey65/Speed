import torch
import numpy as np
import nltk
import json
import pandas as pd

class Chatbot(torch.nn.Module):
def __innit__(self, layerSize, inputs, numEpochs, lr):
        super().__init__()
        self.port = nltk.PorterStemmer()
        self.allWords = []
        self.allLabels = []
        self.dict = dict()
        self.encoder = torch.nn.Sequential (
            torch.nn.Linear(inputs, layerSize),
            torch.nn.ReLU(),
            torch.nn.Linear(layerSize, layerSize//2),
            torch.nn.ReLU(),
            torch.nn.Linear(layerSize//2, layerSize//4),
            torch.nn.ReLU(),
            torch.nn.Linear(layerSize//4, layerSize//8)
        )
        self.decoder = torch.nn.Sequential (
            torch.nn.Linear(layerSize//8, layerSize//4),
            torch.nn.ReLU(),
            torch.nn.Linear(layerSize//4, layerSize//2),
            torch.nn.ReLU(),
            torch.nn.Linear(),
            torch.nn.ReLU(layerSize//2, layerSize),
            torch.nn.Linear(),
            torch.nn.ReLU(layerSize, inputs)
        )
        self.lr = lr
        self.numEpochs = numEpochs
    
    def encode(self, x):
        return self.encoder(x)
    
    def decode(self, x):
        return self.decoder(x)
    
    def getLoss(self, x, y):
        torch.nn.CrossEntropyLoss(x, y)
    
    def token(self, sentence):
        return nltk.tokenize(sentence)
    
    def bagOfWords(self, sentence):
        bog = [0] * len(self.allWords)
        for i in range(0, len(self.allWords)):
            if self.allWords[i] in sentence:
                bog[i] = 1
        return bog
    
    def createTraining(self):
        # Open and read the JSON file
        conversations = []
        with open("Train\\utterances.jsonl", 'r') as f:
            for l in range(0, len(f), 2):
                line = f[l]
                respond = f[l+1]
                lineJson = json.loads(line)
                respJson = json.loads(respond)
                punc = ['.', '?', '!', ',', '\'', "\""]
                line = (lineJson["text"])
                respond = (respJson["text"])
                self.dict.update({line: respond})
                for p in punc:
                    line = line.replace(p, "")
                    respond = respond.replace(p, "")
                self.token(line)
                self.token(respond)
                self.allWords.extend(line)
                self.allLabels.extend(respond)
                conversations.append((line, respond))
        self.all_words = [self.stem(w) for w in self.allWords]
        self.all_words = sorted(set(self.allWords))
        self.allLabels = sorted(set(self.allLabels))
        for i in range(0, len(conversations)):
            x = self.bagOfWords(conversations[i][0])
            y = conversations[i][1].index(conversations[i][1])
            conversations[i] = (x, y)
        return conversations
        

    def train(self, dataset):
        encoderOp = torch.optim.Adam(self.encoder.parameters(), lr=self.lr)
        decoderOp = torch.optim.Adam(self.decoder.parameters(), lr=self.lr)
        for i in range(0, self.numEpochs):
            for j in range(0, len(self.xTrain)):
                words = dataset[j][0]
                prev = words[0]
                pred = []
                for k in words:
                    prev = k
                    self.encoder(k)
                for k in range(0, len(words)):
                    prev = self.decode(prev)
                    pred.append(prev)
                labels = dataset[j][1].split(" ")
                loss = self.getLoss(pred, labels)
                encoderOp.zero_grad()
                decoderOp.zero_grad()
                loss.backward()
                encoderOp.step()
                decoderOp.step()
    
    def predict(self, sentence):
        with open('intents.json', 'r') as json_data:
            intents = json.load(json_data)
            punc = ['.', '?', '!', ',', '\'', "\""]
            for p in punc:
                sentence = sentence.replace(p, "")
            sentence = self.token(sentence)
            X = self.bag_of_words(sentence)
            X = X.reshape(1, X.shape[0])
            output = self.decode(self.encode(X))
            _, predicted = torch.max(output, dim=1)

            tag = self.allLabels[predicted.item()]

            probs = torch.softmax(output, dim=1)
            prob = probs[0][predicted.item()]
            if prob.item() > 0.75:
                for intent in intents['text']:
                    if tag == intent["text"].index:
                        print(f"Bob: {np.random.choice(self.dict.get(intent))}")
            else:
                print("I do not understand...")





def main():
    cb = Chatbot(200, 25, 50, 0.001)
    d = cb.createTraining()
    cb.train(d)
    cb.predict("Hello Jerry")

if __name__=="__main__":
    main()
