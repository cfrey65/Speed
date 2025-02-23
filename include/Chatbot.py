import torch
import numpy
import nltk

class Chatbot(torch.nn.Module):
    def __innit__(self, layerSize, inputs, output):
        super().__init__()
        self.port = nltk.PorterStemmer()
    
    def token(self, sentence):
        return nltk.tokenize(sentence)
    
    def bagOfWords(self, sentence, )